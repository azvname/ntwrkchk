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

//pthread_mutex_t m; // мьютекс для разграничения доступа
//sem_t sem;


int main (int argc, char* argv[]) {
  pid_t pid = fork();
  if(pid < 0) {
    exit(EXIT_FAILURE); // error on call the fork function
  }else if(pid>0){
    exit(EXIT_SUCCESS); // success on call the fork function
  }

  //dbg_printf("1111\n", argv[2]);

  if(setsid() < 0){
    exit(EXIT_FAILURE);
  }

  create_pid();

  //dbg_printf("2222\n", argv[2]);

  if(strncmp(argv[1], "stop", 4)==0){
    down_ppp();

    FILE* prc = popen("pkill v4", "r");
    const int buffer_size=64;
    char buffer[buffer_size];

    if(prc!=NULL) {
      fread(buffer, 1, 63, prc);
      //printf("%s\n", buffer);
    }
    func_signal(-1);
    return 0;

  } else if (strncmp(argv[1], "start", 5)==0) {
    wiringPiSetup();

    int rpin=4;
    int gpin=3;
    int bpin=0;
    pinMode(rpin, OUTPUT);
    pinMode(gpin, OUTPUT);
    pinMode(bpin, OUTPUT);

    thread_pool = malloc(MAX_THREADS*sizeof(pthread_t));
    // memset(thread_pool, 22222, MAX_THREADS);
    __sighandler_t status = signal(SIGINT, func_signal);

    int xl2tpd_state;
    int ppp_state;
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

    while(1){
      // check_device_state();
      // sleep(1);
      // printf("ENGIMA\n");
      set_blue(500);
      usleep(1000*timeout_between_light);
       // check_ssh_state();
      check_device_state();
      usleep(1000*timeout_between_light);

      //continue;
      //printf("--------------------------------> %.6f\n", (double)(end-start)/CLOCKS_PER_SEC);
      if (check_wifi_state() == 1) { 
        // dbg_printf("OK - wifi\n", argv[2]);
        //continue; 
      }else{
        // system("systemctl restart networking.service");
        system("ifdown wlan0");
        system("ifup wlan0");
      }
      usleep(1000*timeout_between_light);

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
      check_ppp_state();
      usleep(1000*timeout_between_light);
      //end = clock();

      check_ssh_state();
      usleep(1000*timeout_between_light);

      check_ethernet_state();
      usleep(1000*timeout_between_light);




    }

    // dbg_printf("Eneded loop!\n", argv[2]);
    // pthread_mutex_destroy(&m);
    //pthread_exit(NULL); // wait untill threads ended.

    free(thread_pool);
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
