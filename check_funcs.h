


void check_device_state() {


}


int check_wifi_state(){
  char buffer[128];
  FILE* fi_wlan = fopen("/sys/class/net/wlan0/carrier", "r");
  if(fi_wlan == NULL) {
    printf("Some error with read wlan0\n");
    // exit(0);
    set_color(4,3,0,100,0,0);
    usleep(1000*1000);
    clear_color(4,3,0);
    usleep(1000*10);

    return -1;
  }
  fgets(buffer, 127, fi_wlan);
  printf("wlan buffer: %c\n", buffer[0]);
  fclose(fi_wlan);
  if(buffer[0]=='0'){
    set_color(4,3,0,100,15,0);
    usleep(1000*1000);
    clear_color(4,3,0);
    usleep(1000*10);
    return 0;
    
  }else{
    set_color(4,3,0,0,20,0);
    usleep(1000*1000);
    clear_color(4,3,0);
    usleep(1000*10);
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
      set_color(4,3,0,90,0,0);
      delayMicroseconds(1000*1000);
      clear_color(4,3,0);
      delayMicroseconds(1000*10);
      return -1;

    }

    if(buffer[0] == '1') {
      set_color(4,3,0,0,20,0);
      delayMicroseconds(1000*1000);
      clear_color(4,3,0);
      delayMicroseconds(1000*10);
      return 1; //interface is up
    }else{
      set_color(4,3,0,90,15,0);
      delayMicroseconds(1000*1000);
      clear_color(4,3,0);
      delayMicroseconds(1000*10);
      return 0; // interface is down
    }

    printf("ppp buffer: %c\n", buffer[0]);


  }
  printf("acc: %d\n", acc);

  set_color(4,3,0,90,0,0);
  delayMicroseconds(1000*2000);
  clear_color(4,3,0);
  delayMicroseconds(1000*10);
  return -1; // interface is not exists





}

void check_ssh_state() {
  usleep(1000*1000);
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

    for(int i=0; i<atoi(&buffer_prc[0]); i++){
      set_color(4,3,0,90,0,40);
      usleep(1000*500);
      clear_color(4,3,0);
      usleep(1000*100);

    }
    pclose(prc);
  }
  //system("w -u|sed -n '1p'|awk '{print $4}'");
  //system("ps aux | grep 'sshd:' |  grep pts | grep -v grep");
  //system("ps aux | grep 'sshd:' |  grep pts |grep -v grep |wc  -l");

  //exit(0);


}

void check_ethernet_state() {
  //FILE* prc = popen("dmesg|grep -i 'link is'|awk '{print $10}'", "r");
  FILE* prc1 = popen("cat /sys/class/net/end0/duplex", "r");

  char buffer1[64];
  memset(buffer1, 0, 64);
  buffer1[63]='\0';
  
  if(prc1!=NULL){
    fread(buffer1, 1, 63, prc1);
    printf("%s\n", buffer1);
    pclose(prc1);

  }




  FILE* prc2 = popen("cat /sys/class/net/end0/speed", "r");
  char buffer2[64];
  memset(buffer2, 0, 64);
  buffer2[63]='\0';
  
  if(prc2!=NULL){
    fread(buffer2, 1, 63, prc2);
    printf("%s\n", buffer2);


    pclose(prc2);

  }

  printf("%s + %s\n", buffer1, buffer2);






}




