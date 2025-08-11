//pthread_t thread_pool[MAX_THREADS]; // identificals array of threads
//pthread_t* thread_pool;


int time_time_timeout = 40;
extern pthread_mutex_t m;
void* color_func(void*);
pthread_t* s_color(rgb_led* , int, int, int);

rgb_led* init_rgb(int rpin, int gpin, int bpin) {

  printf("init_rgb %d %d %d\n", rpin, gpin, bpin);

  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);

  if(rpin == gpin || rpin == bpin || gpin == bpin) {
    printf("Error: the same number of pin");
    return NULL;
  }

  rgb_led* obj = malloc(sizeof(rgb_led));

  obj->red_pin = rpin;
  obj->green_pin = gpin;
  obj->blue_pin = bpin;

  obj->red = 0;
  obj->green = 0;
  obj->blue = 0;


  return obj;
}


void sc_red(rgb_led* color_struct) {
  // digitalWrite(((rgb_led*)color_struct)->red_pin, HIGH);
  // digitalWrite(((rgb_led*)color_struct)->green_pin, LOW);
  // digitalWrite(((rgb_led*)color_struct)->blue_pin, LOW);

  color_struct->red = 100;
  color_struct->green = 0;
  color_struct->blue = 0;
}
void sc_green(rgb_led* color_struct) {
  // digitalWrite(((rgb_led*)color_struct)->red_pin, LOW);
  // digitalWrite(((rgb_led*)color_struct)->green_pin, HIGH);
  // digitalWrite(((rgb_led*)color_struct)->blue_pin, LOW);

  color_struct->red = 0;
  color_struct->green = 10;
  color_struct->blue = 0;
}
void sc_blue(rgb_led* color_struct) {
  // digitalWrite(((rgb_led*)color_struct)->red_pin, LOW);
  // digitalWrite(((rgb_led*)color_struct)->green_pin, LOW);
  // digitalWrite(((rgb_led*)color_struct)->blue_pin, HIGH);

  color_struct->red = 0;
  color_struct->green = 0;
  color_struct->blue = 10;
}
void sc_yellow(rgb_led* color_struct) {
  // digitalWrite(((rgb_led*)color_struct)->red_pin, HIGH);
  // digitalWrite(((rgb_led*)color_struct)->green_pin, HIGH);
  // digitalWrite(((rgb_led*)color_struct)->blue_pin, LOW);

  color_struct->red = 100;
  color_struct->green = 20;
  color_struct->blue = 0;

}






void set_color(int rpin, int gpin, int bpin, int red_value, int green_value, int blue_value) {
  color red_box;
  color green_box;
  color blue_box;

  pthread_t* thread_pool = malloc(MAX_THREADS*sizeof(thread_pool));
  // red_box = malloc(sizeof(color)); 
  red_box.pin=rpin; 
  red_box.current_color=red_value;

  // green_box = malloc(sizeof(color)); 
  green_box.pin=gpin; 
  green_box.current_color=green_value;

  // blue_box = malloc(sizeof(color)); 
  blue_box.pin=bpin; 
  blue_box.current_color=blue_value;

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

  color rgb_boxes[MAX_THREADS]={red_box, green_box, blue_box};
  // for(int i=0;i<MAX_THREADS;i++){
  //   if(pthread_create(&thread_pool[i], NULL, color_func, rgb_boxes[i]) != 0) {
  //     printf("color thread error: %d\n", i);
  //   };
  // }



  /*
  if(pthread_create(&thread_pool[i_red], NULL, color_func, &red_box) != 0) {
    printf("red thread error\n");
  };
  if(pthread_create(&thread_pool[i_green], NULL, color_func, &green_box) != 0) {
    printf("green thread error\n");
  };
  if(pthread_create(&thread_pool[i_blue], NULL, color_func, &blue_box) != 0) {
    printf("blue thread error\n");
  };
  */
  




}

void clear_color(int rpin, int gpin, int bpin){
  pthread_t* thread_pool = malloc(MAX_THREADS * sizeof(pthread_t));

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
    // free(red_box);
  // if(green_box != NULL) 
    // free(green_box);
  // if(blue_box != NULL) 
    // free(blue_box);

  // free(thread_pool);
  // thread_pool = malloc(MAX_THREADS*sizeof(thread_pool));
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  // printf("Clear is done.\n");
}

/*
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
*/

void* red_func(void* color_struct) {
  printf("red_func() is running..\n");
  //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  // printf("pin: %d; saturation: %d\n", ((color*)color_struct)->pin, ((color*)color_struct)->current_color);
  

  rgb_led* led = (rgb_led*)color_struct;

  // int red_color = led->red;
  // int green_color = led->green;
  // int blue_color = led->blue;



  // printf("in red_func() - colors: %d %d %d\n", red_color, green_color, blue_color);

  printf("in red_func() - colors: %d %d %d\n", ((rgb_led*)color_struct)->red, ((rgb_led*)color_struct)->green, ((rgb_led*)color_struct)->blue);
  //if(((rgb_led*)color_struct)->red != 0) {
  for (;;) {

    pthread_testcancel();
    // printf("Infinity looop\n");

    if(((rgb_led*)color_struct)->red != 100) {
      digitalWrite(((rgb_led*)color_struct)->red_pin, LOW);
      delayMicroseconds(time_time_timeout*(100-((rgb_led*)color_struct)->red)); // microseconds
    }

    if(((rgb_led*)color_struct)->red != 0) {
      digitalWrite(((rgb_led*)color_struct)->red_pin , HIGH);
      delayMicroseconds(time_time_timeout*((rgb_led*)color_struct)->red); // microseconds
    }



      
      
      
      
    // pthread_mutex_lock(&led->m);
    // int red_pin = led->red_pin;
    // int green_pin = led->green_pin;
    // int blue_pin = led->blue_pin;
    // int red = led->red;
    // int green = led->green;
    // int blue = led->blue;
    // pthread_mutex_unlock(&led->m);

    // if(red == 0) break;

    // digitalWrite(red_pin, LOW);
    // delayMicroseconds(40*(100-red)); // microseconds
    // digitalWrite(red_pin , HIGH);
    // delayMicroseconds(40*red); // microseconds

    //}
    //usleep(1000*100);

  }

  printf("This mean that Infinity loop ended\n");
  return NULL;
}




void* green_func(void* color_struct) {
  printf("green_func() is running..\n");
  rgb_led* led = (rgb_led*)color_struct;
  //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  // printf("pin: %d; saturation: %d\n", ((color*)color_struct)->pin, ((color*)color_struct)->current_color);
  // printf("in green_func() - colors: %d %d %d\n", red_color, green_color, blue_color);
  printf("in green_func() - colors: %d %d %d\n", ((rgb_led*)color_struct)->red, ((rgb_led*)color_struct)->green, ((rgb_led*)color_struct)->blue);
  for (;;) {
    pthread_testcancel();
    if(((rgb_led*)color_struct)->green!= 100) {
      digitalWrite(((rgb_led*)color_struct)->green_pin, LOW);
      delayMicroseconds(time_time_timeout*(100-((rgb_led*)color_struct)->green)); // microseconds
    }
    if(((rgb_led*)color_struct)->green!= 0) {
      digitalWrite(((rgb_led*)color_struct)->green_pin , HIGH);
      delayMicroseconds(time_time_timeout*((rgb_led*)color_struct)->green); // microseconds
    }

    // pthread_mutex_lock(&led->m);
    // int red_pin = led->red_pin;
    // int green_pin = led->green_pin;
    // int blue_pin = led->blue_pin;
    // int red = led->red;
    // int green = led->green;
    // int blue = led->blue;
    // pthread_mutex_unlock(&led->m);
    // if(green == 0) break;

    // digitalWrite(green_pin, LOW);
    // delayMicroseconds(40*(100-green)); // microseconds
    // digitalWrite(green_pin , HIGH);
    // delayMicroseconds(40*green); // microseconds
    //}
    //usleep(1000*100);

  }
  return NULL;
}

void* blue_func(void* color_struct) {
  printf("blue_func() is running..\n");
  rgb_led* led = (rgb_led*)color_struct;
  //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  // printf("pin: %d; saturation: %d\n", ((color*)color_struct)->pin, ((color*)color_struct)->current_color);
  printf("in blue_func() - colors: %d %d %d\n", ((rgb_led*)color_struct)->red, ((rgb_led*)color_struct)->green, ((rgb_led*)color_struct)->blue);

  for (;;) {
    pthread_testcancel();

    // pthread_mutex_lock(&led->m);
    // int red_pin = led->red_pin;
    // int green_pin = led->green_pin;
    // int blue_pin = led->blue_pin;
    // int red = led->red;
    // int green = led->green;
    // int blue = led->blue;
    // pthread_mutex_unlock(&led->m);
    // if(blue == 0) break;
      
    if(((rgb_led*)color_struct)->blue!= 100) {
      digitalWrite(((rgb_led*)color_struct)->blue_pin, LOW);
      delayMicroseconds(time_time_timeout*(100-((rgb_led*)color_struct)->blue)); // microseconds
    }

    if(((rgb_led*)color_struct)->blue!= 0) {
      digitalWrite(((rgb_led*)color_struct)->blue_pin , HIGH);
      delayMicroseconds(time_time_timeout*((rgb_led*)color_struct)->blue); // microseconds
    }

    // digitalWrite(blue_pin, LOW);
    // delayMicroseconds(40*(100-blue)); // microseconds
    // digitalWrite(blue_pin, HIGH);
    // delayMicroseconds(40*blue); // microseconds
    //usleep(1000*100);
    

  }

  return NULL;
}

/*
void set_blue(size_t millesec) { 
  set_color(4,3,0,0,0,100);
  delayMicroseconds(1000*millesec);
  clear_color(4,3,0);
  delayMicroseconds(1000*10);
}

void set_yellow(size_t millesec) { 
  set_color(4,3,0,90,15,0);
  delayMicroseconds(1000*millesec);
  clear_color(4,3,0);
  delayMicroseconds(1000*10);
}

void set_green(size_t millesec) {
  set_color(4,3,0,0,20,0);
  delayMicroseconds(1000*millesec);
  clear_color(4,3,0);
  delayMicroseconds(1000*10);
}

void set_red(size_t millesec) {
  set_color(4,3,0,100,0,0);
  delayMicroseconds(1000*millesec);
  clear_color(4,3,0);
  delayMicroseconds(1000*10);
}
*/





/*
void set_blue_t(int r, int g, int b, size_t millesec) { 
  s_color(r,g,b,0,0,100);
  delayMicroseconds(1000*millesec);
  clear_color(r,g,b);
  delayMicroseconds(1000*10);
}

void set_yellow_t(int r, int g, int b, size_t millesec) { 
  s_color(r,g,b,90,15,0);
  delayMicroseconds(1000*millesec);
  clear_color(r,g,b);
  delayMicroseconds(1000*10);
}

void set_green_t(int r, int g, int b, size_t millesec) {
  s_color(r,g,b,0,20,0);
  delayMicroseconds(1000*millesec);
  clear_color(r,g,b);
  delayMicroseconds(1000*10);
}

void set_red_t(int r, int g, int b, size_t millesec) {
  s_color(r,g,b,100,0,0);
  delayMicroseconds(1000*millesec);
  clear_color(r,g,b);
  delayMicroseconds(1000*10);
}



void test_rgb_led(int r, int g, int b) {
  set_red_t(r,g,b,500);
  set_green_t(r,g,b,500);
  set_blue_t(r,g,b,500);
}
*/


pthread_t* s_color(rgb_led* rgbled, int r, int g, int b) {
  printf("s_color() is running\n");

  printf("INFO::: colors: %d %d %d\n", rgbled->red, rgbled->green, rgbled->blue);


  rgb_led copy_rgbled = *rgbled;

  rgb_led copy_copy_rgbled = copy_rgbled;

  printf("original rgbled: %X\n", rgbled);
  printf("copy rgbled: %X\n", copy_rgbled);
  printf("copy copy rgbled: %X\n", copy_copy_rgbled);

  // new value for the led
  rgbled->red = r;
  rgbled->green = g;
  rgbled->blue = b;

  printf("INFO::: colors: %d %d %d\n", rgbled->red, rgbled->green, rgbled->blue);

  void* (*paint_func[MAX_THREADS])(void* color_struct) =  {red_func, green_func, blue_func};



  printf("Created thread_pool\n");
  pthread_t* thread_pool = malloc(MAX_THREADS * sizeof(pthread_t));

  printf("Run threads\n");


  for(int i=0;i<MAX_THREADS;i++){
    printf("%X\n", thread_pool[i]);
    if(pthread_create(&thread_pool[i], NULL, paint_func[i], rgbled) != 0) {
      switch(i) {
        case i_red:
          printf("Red thread error\n");
          break;
        case i_green:
          printf("Green thread error\n");
          break;
        case i_blue:
          printf("Blue thread error\n");
          break;
      }
      exit(0);
    }else {
      printf("Thread %d success was running\n",  i);
    }


  }

  // for(int i=0;i<MAX_THREADS;i++) {
  //   printf("Joined %d\n", i);
  //   pthread_join(pthr1[i], NULL);
  //
  // }
  
  return thread_pool;

}





void test_zalupa_pwm_shit_huy() {
  // pthread_mutex_init(&led1->m, NULL);

  int local_timeout = 100;

  for(;;){

  usleep(1000*local_timeout);
  // pthread_mutex_lock(&led1->m);
  led_arr[0]->red=100;
  led_arr[0]->green = 0;
  led_arr[0]->blue=50;
  // pthread_mutex_unlock(&led1->m);

  // pthread_cancel(pthr1);

  usleep(1000*local_timeout);
  led_arr[1]->red=100;
  led_arr[1]->green = 0;
  led_arr[1]->blue=50;
  // pthread_cancel(pthr2);

  usleep(1000*local_timeout);
  led_arr[2]->red=100;
  led_arr[2]->green = 0;
  led_arr[2]->blue=50;
  // pthread_cancel(pthr3);

  usleep(1000*local_timeout);
  led_arr[3]->red=100;
  led_arr[3]->green = 0;
  led_arr[3]->blue=50;
  // pthread_cancel(pthr4);

  usleep(1000*local_timeout);
  led_arr[4]->red=100;
  led_arr[4]->green = 0;
  led_arr[4]->blue=50;
  // pthread_cancel(pthr5);
  for(;;);
  continue;

  usleep(1000*local_timeout);
  led_arr[0]->red=100;
  led_arr[0]->green = 10;
  led_arr[0]->blue=0;

  usleep(1000*local_timeout);
  led_arr[1]->red=100;
  led_arr[1]->green = 10;
  led_arr[1]->blue=0;

  usleep(1000*local_timeout);
  led_arr[2]->red=100;
  led_arr[2]->green = 10;
  led_arr[2]->blue=0;

  usleep(1000*local_timeout);
  led_arr[3]->red=100;
  led_arr[3]->green = 10;
  led_arr[3]->blue=0;

  usleep(1000*local_timeout);
  led_arr[4]->red=100;
  led_arr[4]->green = 10;
  led_arr[4]->blue=0;
  }

}
