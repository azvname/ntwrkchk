

#define MAX_THREADS 3
#define true 1
enum rgb {i_red, i_green, i_blue};
pthread_t* thread_pool[5];

typedef struct {
  int pin;
  int current_color;
} color;

typedef struct {
  int red_pin;
  int green_pin;
  int blue_pin;

  int red;
  int green;
  int blue;


  int current_color;
  pthread_mutex_t m;

} rgb_led;




rgb_led* led_arr[5];






void dbg_printf(const char* str, const char* state) {
  if (strncmp(state, "on", 2) != 0) printf("%s", str);
}



void down_ppp();




void func_signal(int arg) {
  printf("AHTUNG program to be ended\n");
  printf("Argument: %d\n", arg);


  usleep(1000*1000);
  down_ppp();
  usleep(1000*1000);
  

  // led_arr

  for(int i=0;i<5;i++) { 
    if(thread_pool[i] != 0) {
      pthread_cancel(thread_pool[i][0]);
      pthread_cancel(thread_pool[i][1]);
      pthread_cancel(thread_pool[i][2]);
      if (pthread_join(thread_pool[i][0], NULL) != 0) {}
      if (pthread_join(thread_pool[i][1], NULL) != 0) {}
      if (pthread_join(thread_pool[i][2], NULL) != 0) {}
    }


  }

  //for(;;);
  for(int i=0;i<5;i++) {


    if(led_arr[i] != 0) {
      printf("INFO::SIGNAL::FUNC: colors: %d %d %d\n", led_arr[i]->red, led_arr[i]->green, led_arr[i]->blue);
      printf("INFO::SIGNAL::FUNC: pins: %d %d %d\n", led_arr[i]->red_pin, led_arr[i]->green_pin, led_arr[i]->blue_pin);

      digitalWrite(led_arr[i]->red_pin, LOW);
      digitalWrite(led_arr[i]->green_pin, LOW);
      digitalWrite(led_arr[i]->blue_pin, LOW);
    }

  }
  // printf("INFO::SIGNAL::FUNC: colors: %d %d %d\n", arg->red, arg->green, arg->blue);

  // down_ppp();


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

void down_ppp() {
  FILE* fo=fopen("/var/run/xl2tpd/l2tp-control", "w");
  if(fo!=NULL){
    fprintf(fo,"%s","d vpn-connection");
    fclose(fo);

  }else{
    printf("Fail on run down_ppp()\n");
    //return - 1;
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


