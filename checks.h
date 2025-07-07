void check_device_state() {
  // some other varian "systemctl --quiet --failed |wc -l"
  // sudo dmesg -H |grep -i error



  FILE* prc = popen("systemctl is-active multi-user.target", "r");
  const int buffer_device_state_size=64;
  char buffer_device_state[buffer_device_state_size];

  if(prc!=NULL) {
    fread(buffer_device_state, 1, 63, prc);

    if(WEXITSTATUS(pclose(prc)) == -1){
      set_yellow(500);
      return;
    }
    if(strncmp(buffer_device_state, "active", 6) == 0) {
      set_green(500);
      return;
      //return 1; //daemon is active
    }else{
      set_red(500);
      return;
      //return 0; // daemon is inactive
    }


  }

  set_red(500);
  return;



}

int check_wifi_state(){
  char buffer[128];
  FILE* fi_wlan = fopen("/sys/class/net/wlan0/carrier", "r");
  if(fi_wlan == NULL) {
    printf("Some error with read wlan0\n");
    // exit(0);
    set_red(1000);
    return -1;
  }
  fgets(buffer, 127, fi_wlan);
  printf("wlan buffer: %c\n", buffer[0]);
  fclose(fi_wlan);
  if(buffer[0]=='0'){
    set_yellow(1000);
    return 0;
    
  }else{
    set_green(1000);
    return 1;

  }

  //set_color(4,3,0,0,0,90);

}

int check_xl2tpd_state() {
  FILE* prc = popen("systemctl is-active xl2tpd.service", "r");

  char buffer[128];
  memset(buffer, 0, 128);
  buffer[127]='\0';

  if(prc != NULL){
    fread(buffer,1,127, prc);

    if(WEXITSTATUS(pclose(prc)) == 1){
      return -1;
    }
    if(strncmp(buffer, "active", 6) == 0) {
      return 1; //daemon is active
    }else{
      return 0; // daemon is inactive
    }

  }

  return -1; // interface is not exists





}


int check_ppp_state() {
  //set_color(4,3,0,0,90,0);
  //usleep(1000*1000*2);
  FILE* fi_ppp;
  fi_ppp = popen("cat /sys/class/net/ppp*/carrier", "r");
  // fi_ppp = popen("ls", "r");
  char buffer[128];
  memset(buffer, 0, 127);
  buffer[127]='\0';

  static int acc=0;
  acc+=1;

  printf("---> %d ---> %d\n", fi_ppp, errno == EINVAL);
  if(fi_ppp!=NULL) {
    //fgets(buffer, 127, fi_ppp);
    fread(buffer, 1, 127, fi_ppp);
    //pclose(fi_ppp);
    if(WEXITSTATUS(pclose(fi_ppp)) == 1) {
      set_red(1000);
      return -1;

    }

    if(buffer[0] == '1') {
      set_green(1000);
      return 1; //interface is up
    }else{
      set_yellow(1000);
      return 0; // interface is down
    }

    printf("ppp buffer: %c\n", buffer[0]);


  }
  printf("acc: %d\n", acc);

  set_red(500);
  return -1; // interface is not exists





}

void check_ssh_state() {
  //usleep(1000*1000);

  char buffer_prc[256];
  memset(buffer_prc, 0, 255);
  buffer_prc[255]='\0';

  //fflush(3);
  FILE* prc = popen("ps aux | grep 'sshd:' |  grep pts |grep -v grep | wc  -l", "r");
  // FILE* prc = popen("", "r");
  if(prc == NULL) {
    printf("Happen some error\n");
  }else{
    fread(buffer_prc, 1, 255, prc);
    printf("Output from prc: %s\n", buffer_prc);

    if(atoi(&buffer_prc[0]) > 0) {
      set_green(500);
    }else{
      set_red(500);
    }
    // for(int i=0; i<atoi(&buffer_prc[0]); i++){
    //   set_color(4,3,0,90,0,40);
    //   usleep(1000*500);
    //   clear_color(4,3,0);
    //   usleep(1000*100);
    //
    // }
    pclose(prc);
  }


  // FILE* prc_check_connect = popen("journalctl -b|tail -20|grep -i sshd", "r");


  FILE* prc_check_connect = popen("journalctl --since \"30 sec ago\"", "r");
  static int last_state_ssh=0; // 0 - disconnect, 1 - attemption failure, 2 - success

  const int buffer_state_ssh_size = 1024;
  char buffer_state_ssh[buffer_state_ssh_size];
  memset(buffer_state_ssh, 0, buffer_state_ssh_size);
  if(prc_check_connect!=NULL){
    fread(buffer_state_ssh, 1, buffer_state_ssh_size, prc_check_connect);
    //printf("%s\n", strstr(buffer_state_ssh, "a"));
    if (strstr(buffer_state_ssh, "sshd") != NULL) {
      if (strstr(buffer_state_ssh, "fail") != NULL || strstr(buffer_state_ssh, "Invalid user") != NULL) {
        printf("Invalid user\n");
        set_yellow(500);
        last_state_ssh=1;
      }

    }

    // printf("%s\n", NULL);

    // switch (last_state_ssh) {
    //   case 0:
    //     set_red(500);
    //     break;
    //   case 1:
    //     set_yellow(500);
    //     break;
    //   case 2:
    //     set_green(500);
    //     break;
    //   default:
    //     break;
    // }

    pclose(prc_check_connect);
  }











  //system("w -u|sed -n '1p'|awk '{print $4}'");
  //system("ps aux | grep 'sshd:' |  grep pts | grep -v grep");
  //system("ps aux | grep 'sshd:' |  grep pts |grep -v grep |wc  -l");

  //exit(0);


}

void check_ethernet_state() {
  //FILE* prc = popen("dmesg|grep -i 'link is'|awk '{print $10}'", "r");
  FILE* prc1 = popen("cat /sys/class/net/end0/duplex", "r");
  const int buffer_size = 10;
  char buffer_duplex[buffer_size];
  memset(buffer_duplex, 0, buffer_size);
  
  
  if(prc1!=NULL){
    fread(buffer_duplex, 1, buffer_size, prc1);
    // printf("%s\n", buffer_duplex);
    pclose(prc1);

  }




  FILE* prc2 = popen("cat /sys/class/net/end0/speed", "r");
  char buffer_speed[buffer_size];
  memset(buffer_speed, 0, buffer_size);

  
  if(prc2!=NULL){
    fread(buffer_speed, 1, buffer_size, prc2);
    // printf("%s\n", buffer_speed);
    pclose(prc2);

  }


  if(strncmp(buffer_duplex, "full", 4) == 0 && (strncmp(buffer_speed, "1000", 4) == 0 || strncmp(buffer_speed, "100", 3) == 0)) {
    set_green(500);
  }else if( (strncmp(buffer_duplex, "half", 4) == 0 && (strncmp(buffer_speed, "100", 3) == 0 || strncmp(buffer_speed, "10", 2) == 0)) ||
      (strncmp(buffer_duplex, "full", 4) == 0 && strncmp(buffer_speed, "10", 2) == 0) ) {
    set_yellow(500);

  }else{
    set_red(500);
  }
  // printf("CHECKER: %s %s\n", buffer_duplex, buffer_speed);
  // strcat(buffer_duplex, buffer_speed);

  printf("%s\n", buffer_duplex);
  printf("%s\n", buffer_speed);
  // buffer_duplex[strlen(buffer_duplex)-1]='/';
  // sprintf(buffer_duplex + strlen(buffer_duplex), "%s\n",  buffer_speed);
  // buffer_duplex[strlen(buffer_duplex) - 2]='\0';
  // printf("buffer_duplex: %s %d\n", buffer_duplex, strlen(buffer_duplex));
  // printf("buffer_speed: %s %d\n", buffer_speed, strlen(buffer_speed));





}
