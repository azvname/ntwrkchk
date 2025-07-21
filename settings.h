void func_signal(int sig) {
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  printf("Сработал обработчик сигналов.\n");
  exit(0);

}

void up_ppp() {
  FILE* fo = fopen("/var/run/xl2tpd/l2tp-control", "w");
  if(fo != NULL) {
    fprintf(fo, "%s", "c vpn-connection");
    fclose(fo);

  }else{
    printf("Fail on run up_ppp()\n");
  }
}

void create_pid(){
  FILE* fo=fopen("/run/v4.pid", "w");
  if(fo != NULL){
    fprintf(fo, "%d", getpid());
    fclose(fo);
  }else{
    printf("FAIL - on create /run/v4.pid\n");
  }
}

