# ntwrkchk


## Подключение светодиода
# Красный - 10
# Зелёный - 8
# Синий - 3


![Куда что подключать](https://raw.githubusercontent.com/azvname/ntwrkchk/92503367fb67c9dda642ebdb4323ecf819541556/pinout.jpg)



## Установите зависимости
```sh
sudo apt install gcc g++ git
git clone https://github.com/orangepi-xunlong/wiringOP.git
cd wiringOP
sudo ./build clean
sudo ./build
cd

```



## Компиляция
```sh
git clone https://github.com/azvname/ntwrkchk.git
cd ntwrkchk
gcc main.c -lwiringPi -o v4

```
## Отредактируйте файл сервиса l2tp_up.serivce: укажите свой путь в ExecStart. 

## Активируем демон
```sh
mv l2tp_up.service /etc/systemd/system
sudo systemctl enable --now l2tp_up.service
```


## Перезагрузите устройство
