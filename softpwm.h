
#define MAX_THREADS 3
enum rgb {i_red, i_green, i_blue};



//pthread_t thread_pool[MAX_THREADS]; // identificals array of threads
pthread_t* thread_pool;

typedef struct {
  int pin;
  int current_color;
} color;

color* red_box = NULL;
color* green_box = NULL;
color* blue_box = NULL;


void* color_func(void*);


void set_color(int rpin, int gpin, int bpin, int red_value, int green_value, int blue_value) {
  red_box = malloc(sizeof(color)); 
  red_box->pin=rpin; 
  red_box->current_color=red_value;

  green_box = malloc(sizeof(color)); 
  green_box->pin=gpin; 
  green_box->current_color=green_value;

  blue_box = malloc(sizeof(color)); 
  blue_box->pin=bpin; 
  blue_box->current_color=blue_value;

  //rgb_boxes = malloc(MAX_THREADS*sizeof(color));
  // printf("%d %d %d\n", red_value, green_value, blue_value);

  // red = {3, 30*100/255};
  // thread_pool[i_red]=i_red;
  // thread_pool[i_green]=i_green;
  // thread_pool[i_blue]=i_blue;

  // for(int i=0;i<MAX_THREADS;i++){
  //   thread_pool[i] = ++thread_identical;
  // }

  //color rgb_boxes[MAX_THREADS];

  color* rgb_boxes[MAX_THREADS]={red_box, green_box, blue_box};
  // for(int i=0;i<MAX_THREADS;i++){
  //   if(pthread_create(&thread_pool[i], NULL, color_func, rgb_boxes[i]) != 0) {
  //     printf("color thread error: %d\n", i);
  //   };
  // }




  if(pthread_create(&thread_pool[i_red], NULL, color_func, red_box) != 0) {
    printf("red thread error\n");
  };
  if(pthread_create(&thread_pool[i_green], NULL, color_func, green_box) != 0) {
    printf("green thread error\n");
  };
  if(pthread_create(&thread_pool[i_blue], NULL, color_func, blue_box) != 0) {
    printf("blue thread error\n");
  };
  




}

void clear_color(int rpin, int gpin, int bpin){
  for(int i=0;i<MAX_THREADS;i++){
    // printf("Clear is started %d\n", i);
    if(pthread_cancel(thread_pool[i]) != 0) {
      printf("On exec pthread_cancel happen some error\n");
      return;
    };
    // printf("tam param param tam param%d\n", i);
    if (pthread_join(thread_pool[i], NULL) != 0) {
      printf("On exec pthread_join happen some error\n");
      return;

    };
    //thread_pool[i]=i+MAX_THREADS;
  }

  //memset(thread_pool, 22222, MAX_THREADS);
  // if(red_box != NULL) 
    free(red_box);
  // if(green_box != NULL) 
    free(green_box);
  // if(blue_box != NULL) 
    free(blue_box);

  // free(thread_pool);
  // thread_pool = malloc(MAX_THREADS*sizeof(thread_pool));
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  // printf("Clear is done.\n");
}

void* color_func(void* color_struct) {
  //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  // printf("pin: %d; saturation: %d\n", ((color*)color_struct)->pin, ((color*)color_struct)->current_color);
  for (;;) {
    if(((color*)color_struct)->current_color != 0) {
      digitalWrite(((color*)color_struct)->pin, LOW);
      delayMicroseconds(40*(100-((color*)color_struct)->current_color)); // microseconds
      digitalWrite(((color*)color_struct)->pin , HIGH);
      delayMicroseconds(40*((color*)color_struct)->current_color); // microseconds
    }
    pthread_testcancel();

  }
  return NULL;
}


void func_signal(int sig) {
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  printf("Сработал обработчик сигналов.\n");
  exit(0);

}



