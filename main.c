#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// #include <semaphore.h>
#include <string.h>
#include <errno.h>

//#include <time.h>
#include <sys/time.h> // Для gettimeofday
#include <sys/sysinfo.h>
#include <linux/kernel.h>




#include "settings.h"
#include "softpwm.h"
#include "checks.h"

pthread_mutex_t m; // мьютекс для разграничения доступа
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
//sem_t sem;


// int arr_color_bled[5][3] = {{10,0,0},{0,10,0},{0,0,10},{10,0,0},{0,10,0}};
// void set_all_led(int acc_acc){
//   if(led_arr[acc_acc] != 0) {
//     led_arr[0]->red_pin = arr_color_bled[acc_acc][0];
//     led_arr[0]->green_pin = arr_color_bled[acc_acc][1];
//     led_arr[0]->blue_pin = arr_color_bled[acc_acc][2];
//     usleep(1000*1000);
//
//     led_arr[1]->red_pin = arr_color_bled[acc_acc][0];
//     led_arr[1]->green_pin = arr_color_bled[acc_acc][1];
//     led_arr[1]->blue_pin = arr_color_bled[acc_acc][2];
//     usleep(1000*1000);
//
//     led_arr[2]->red_pin = arr_color_bled[acc_acc][0];
//     led_arr[2]->green_pin = arr_color_bled[acc_acc][1];
//     led_arr[2]->blue_pin = arr_color_bled[acc_acc][2];
//     usleep(1000*1000);
//
//     led_arr[3]->red_pin = arr_color_bled[acc_acc][0];
//     led_arr[3]->green_pin = arr_color_bled[acc_acc][1];
//     led_arr[3]->blue_pin = arr_color_bled[acc_acc][2];
//     usleep(1000*1000);
//
//     led_arr[4]->red_pin = arr_color_bled[acc_acc][0];
//     led_arr[4]->green_pin = arr_color_bled[acc_acc][1];
//     led_arr[4]->blue_pin = arr_color_bled[acc_acc][2];
//     usleep(1000*1000);
//
//
//   }
//
//
// }

int main(int argc, char* argv[]) {

  pid_t pid = fork();
  if(pid < 0) {
    exit(EXIT_FAILURE); // error on call the fork function
  }else if(pid>0){
    exit(EXIT_SUCCESS); // success on call the fork function
  }

  // dbg_printf("1111\n", argv[2]);

  if(setsid() < 0){
    exit(EXIT_FAILURE);
  }

  create_pid();







  __sighandler_t status = signal(SIGINT, func_signal);
  printf("Start\n");
  wiringPiSetup();
  printf("init_rgb()\n");

  memset(led_arr, 0, 5);





  //test_zalupa_pwm_shit_huy();
  //for(;;);


  if(strncmp(argv[1], "stop", 4)==0){
    printf("Stopped works\n");
    down_ppp();

    usleep(1000*1000*10);
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


    usleep(1000*1000*10);
    for(int i=0;i<5;i++) {


      if(led_arr[i] != 0) {
        printf("INFO::SIGNAL::FUNC: colors: %d %d %d\n", led_arr[i]->red, led_arr[i]->green, led_arr[i]->blue);
        printf("INFO::SIGNAL::FUNC: pins: %d %d %d\n", led_arr[i]->red_pin, led_arr[i]->green_pin, led_arr[i]->blue_pin);

        digitalWrite(led_arr[i]->red_pin, LOW);
        digitalWrite(led_arr[i]->green_pin, LOW);
        digitalWrite(led_arr[i]->blue_pin, LOW);
      }

    }


    //func_signal(-1);
    //FILE* prc = popen("pkill v4", "r");
    //const int buffer_size=64;
    //char buffer[buffer_size];

    //printf("hello world\n");
    //if(prc==NULL) {
    //  fread(buffer, 1, 63, prc);
    //  exit(0);
    //  //printf("%s\n", buffer);
    //}
    //printf("hello world\n");



    return 0;

  } else if (strncmp(argv[1], "start", 5)==0) {
    rgb_led* led1;
    if((led1=init_rgb(4,3,0)) == NULL) {
      printf("Error on init_rgb\n");
      exit(0);
    }
    led_arr[0] = led1;
    printf("s_color()\n");
    pthread_t* pthr1 = s_color(led1,100,0,0);

    thread_pool[0] = pthr1;
    //sc_red(led1);
  



    rgb_led* led2;
    if((led2=init_rgb(1,2,5)) == NULL) {
      printf("Error on init_rgb\n");
      exit(0);
    }
    led_arr[1] = led2;
    printf("s_color()\n");
    pthread_t* pthr2 = s_color(led2,100,0,0); // создаётся новый пул потоков в pthr2
    //sc_green(led2);
    thread_pool[1] = pthr2;



    
    rgb_led* led3;
    if((led3=init_rgb(7,8,11)) == NULL) {
      printf("Error on init_rgb\n");
      exit(0);
    }
    led_arr[2] = led3;
    printf("s_color()\n");
    pthread_t* pthr3 = s_color(led3,100,0,0);
    // sc_blue(led3);
    // usleep(1000*1000*2);
    // sc_red(led3);
    thread_pool[2] = pthr3;



    rgb_led* led4;
    if((led4=init_rgb(12,14,17)) == NULL) {
      printf("Error on init_rgb\n");
      exit(0);
    }
    led_arr[3] = led4;
    printf("s_color()\n");
    pthread_t* pthr4 = s_color(led4,100,0,0);
    //sc_yellow(led4);
    thread_pool[3] = pthr4;
  


    rgb_led* led5;
    if((led5=init_rgb(18,19,16)) == NULL) {
      printf("Error on init_rgb\n");
      exit(0);
    }
    led_arr[4] = led5;
    printf("s_color()\n");
    pthread_t* pthr5 = s_color(led5,100,0,0);
    thread_pool[4] = pthr5;


    printf("Start TEST\n");

    // for(int i=0;i<MAX_THREADS;i++) {
    //   printf("Joined %d\n", i);
    //   // pthread_join(pthr1[i], NULL);
    //   // pthread_join(pthr2[i], NULL);
    //   // pthread_join(pthr3[i], NULL);
    //   // pthread_join(pthr4[i], NULL);
    //   // pthread_join(pthr5[i], NULL);
    //
    //
    // }
    

    

    // func_signal(-1);

    // for(;;){
    //   test_rgb_led(3, 4, 0);
    //   test_rgb_led(1, 2, 5);
    //   test_rgb_led(7, 8, 11);
    //   test_rgb_led(12, 14, 17);
    //   test_rgb_led(18, 19, 20);
    // }

    printf("This mean that general thread is ended\n");
    //return 0;








  //dbg_printf("2222\n", argv[2]);

    /*
    int rpin=4;
    int gpin=3;
    int bpin=0;

    init_rgb(4,3,0);
    // memset(thread_pool, 22222, MAX_THREADS);
    */

    int xl2tpd_state;
    int ppp_state;
    /*
    // int is_the_not_first_attempt=1;
    int timeout_between_light = 500;
    //int start=0, end=0;
    //start = clock();

      // структуры для замера начала и завершения времени
    // struct timeval start_tv, end_tv;
    // long long start_us, end_us;
    // double elapsed_ms;

    // Начало отсчета времени
    // gettimeofday(&start_tv, NULL);




    //dbg_printf("Started loop!\n", argv[2]);
    */

    while(1){
      // check_device_state();
      // sleep(1);
      // printf("ENGIMA\n");
      //set_blue(500);
      //usleep(1000*timeout_between_light);
       // check_ssh_state();
      check_device_state(led1);
      //usleep(1000*timeout_between_light);

      //continue;
      //printf("--------------------------------> %.6f\n", (double)(end-start)/CLOCKS_PER_SEC);
      if (check_wifi_state(led2) == 1) { 
        // dbg_printf("OK - wifi\n", argv[2]);
        //continue; 
      }else{
        // system("systemctl restart networking.service");
        system("ifdown wlan0");
        system("ifup wlan0");
      }
      //usleep(1000*timeout_between_light);

      if ((xl2tpd_state=check_xl2tpd_state()) == 0) {
        //dbg_printf("xl2tpd не запущен по этому - запускаюсь!\n", argv[2]);
        system("/etc/init.d/xl2tpd start");
        // dbg_printf("OK - xl2tpd\n", argv[2]);
        //continue;
      }

      // if ((ppp_state=check_ppp_state()) != 1) { 
      //   printf("ppp не запущен по этому - запускаюсь!\n");
      //   //system("echo \"c vpn-connection\"|tee /var/run/xl2tpd/l2tp-control");
      //   FILE* fo = fopen("/var/run/xl2tpd/l2tp-control", "w");
      //   fprintf(fo, "%s", "c vpn-connection");
      //   fclose(fo);
      //
      //   usleep(1000*1000*5);
      //   printf("PPP is UP\n");
      //
      //
      //   // is_the_not_first_attempt = 2;
      //   //continue; 
      // } 
      check_ppp_state(led3);
      //usleep(1000*timeout_between_light);
      //end = clock();

      check_ssh_state(led4);
      //usleep(1000*timeout_between_light);

      check_ethernet_state(led5);
      //usleep(1000*timeout_between_light);




    }

    // dbg_printf("Eneded loop!\n", argv[2]);
    // pthread_mutex_destroy(&m);
    //pthread_exit(NULL); // wait untill threads ended.

    //free(thread_pool);

    // dbg_printf("Programm success ended.\n", argv[2]);
    // pthread_join(thread_pool[i_red], NULL);
    // pthread_join(thread_pool[i_green], NULL);
    // pthread_join(thread_pool[i_blue], NULL);
    func_signal(-1);

  }else{
    dbg_printf("no no no no no\n", argv[2]);

    return -1;

  }
  //delay(1000*1000); //milliseconds
  //printf("Start new cycle\n");
  //for (i= 10 ; i!= 0 ; i--) {
  //  // delayMicroseconds(d);
  //  digitalWrite( 21, LOW);
  //  delay(1000*1000);
  //  //delay(2);
  //  digitalWrite( 21 , HIGH);
  //  delay(1000*1000);
  //  //delayMicroseconds(d);
  //  //delay(2);
  //}
  return ( 0 );
}
