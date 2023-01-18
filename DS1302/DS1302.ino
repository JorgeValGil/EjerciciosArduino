#include <virtuabotixRTC.h>
// CLK -> 6 , DAT -> 7, RST -> 8
virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  Serial.begin(9600);
  // Formato para la fecha: segundos, minutos, horas, día de la semana, día del mes, mes, año
  // Comentar la línea, una vez configurado
  //myRTC.setDS1302Time(30, 14, 19, 2, 18, 1, 2023);
}

void loop() {
  myRTC.updateTime();
  dayOfWeek(myRTC.dayofweek);
  Serial.print(", ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  int minutes = myRTC.minutes;
  if (minutes < 10) {
    Serial.print("0");
  }
  Serial.print(minutes);
  Serial.print(":");
  int seconds = myRTC.seconds;
  if (seconds < 10) {
    Serial.print("0");
  }
  Serial.println(seconds);

  delay(1000);
}

void dayOfWeek(int day) {
  switch (day) {
    case 1:
      Serial.print("Domingo");
      break;
    case 2:
      Serial.print("Lunes");
      break;
    case 3:
      Serial.print("Martes");
      break;
    case 4:
      Serial.print("Miércoles");
      break;
    case 5:
      Serial.print("Jueves");
      break;
    case 6:
      Serial.print("Viernes");
      break;
    case 7:
      Serial.print("Sábado");
      break;
  }
}