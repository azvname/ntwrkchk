void func_signal(int sig) {
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  printf("Сработал обработчик сигналов.\n");
  exit(0);

}


