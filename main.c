#include "tm4c123gh6pm.h"
#include "Bomberman.h"
#include "Nokia5110.h"
#include "UART.h"
#include "Audio.h"

// Reset         (RST, pin 1) => PA7
// SSI0Fss       (CE,  pin 2) => PA3
// Data/Command  (DC,  pin 3) => PA6
// SSI0Tx        (Din, pin 4) => PA5
// SSI0Clk       (Clk, pin 5) => PA2
// 3.3V          (Vcc, pin 6)
// back light    (BL,  pin 7)
// Ground        (Gnd, pin 8)
#include "PLL.h"
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


uint8_t escenario[504];
const uint8_t juegoinicio [] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x53, 0x03,
        0x27, 0xFF, 0x1F, 0x0F, 0x4F, 0x0F, 0x1F, 0xFF, 0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xCF, 0x0F, 0x1F,
        0xFF, 0x03, 0x03, 0x4F, 0x0F, 0x1F, 0xFF, 0x1F, 0x0F, 0xAF, 0x8F, 0x9F, 0xFF, 0x0F, 0x0F, 0xDF,
        0xCF, 0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xCF, 0x0F, 0x1F, 0xFF, 0x6F, 0x2F, 0xAF, 0x0F, 0x1F, 0xFF,
        0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x07, 0x63, 0x33, 0x33, 0x01, 0x04,
        0x0E, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE,
        0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,
        0xFC, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
const uint8_t juegoinicio2 [] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x53, 0x03,
        0x27, 0xFF, 0x1F, 0x0F, 0x4F, 0x0F, 0x1F, 0xFF, 0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xCF, 0x0F, 0x1F,
        0xFF, 0x03, 0x03, 0x4F, 0x0F, 0x1F, 0xFF, 0x1F, 0x0F, 0xAF, 0x8F, 0x9F, 0xFF, 0x0F, 0x0F, 0xDF,
        0xCF, 0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xCF, 0x0F, 0x1F, 0xFF, 0x6F, 0x2F, 0xAF, 0x0F, 0x1F, 0xFF,
        0x0F, 0x0F, 0xDF, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x07, 0x63, 0x33, 0x33, 0x01, 0x04,
        0x0E, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE,
        0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE,
        0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE,
        0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,
        0xFC, 0xFC, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xBF, 0xBF, 0x5F, 0x5F, 0xFF, 0xFF, 0x0F, 0x0F, 0xAF, 0x8F, 0xFF, 0x1F, 0x1F, 0xFF,
        0x1F, 0xFF, 0x0F, 0xFF, 0xFF, 0x9F, 0x5F, 0xFF, 0x3F, 0x1F, 0x5F, 0x9F, 0xFF, 0xFF, 0xFF, 0x1F,
        0xFF, 0x1F, 0xFF, 0x1F, 0x1F, 0xDF, 0x1F, 0xFF, 0xFF, 0x1F, 0x5F, 0x1F, 0xFF, 0xFF, 0xFF, 0xDF,
        0x0F, 0xDF, 0x3F, 0x1F, 0x5F, 0x9F, 0xFF, 0x3F, 0x1F, 0xDF, 0x9F, 0xFF, 0x0F, 0xFF, 0xFF, 0x1F,
        0x5F, 0x1F, 0xFF, 0xFF, 0x5F, 0x5F, 0xBF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFF,
        0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};


void Retardo(uint32_t num){
    uint32_t i;
    for(i=0;i<num;i++);
}

int main(void){
   /////////////////////// DECLARACIÓN DE VARIABLES ///////////////////////////
  float conteoFrecuencia = Delay;
  uint8_t FrecuenciaActual = 0;
  uint8_t map[columnas][filas];
  uint32_t i;
  Personaje j1;
  Personaje j2;
  uint16_t temp=0;
  uint8_t BombasActivas[2]= {0,0} ; //BombaActivas[0] = BombasActivasJ1 , BombaActivas[1] = BombasActivasJ2
  Bomb Bomba[BombasMax*2] = {0};
  uint8_t datoRx;
  uint16_t explosion = 0 ,tempInicial=0, condicion =0;


  ///////////////////////// CONFIGURACIÓN DE PUERTOS //////////////////////////

  ConfiguraPWM();
  PLL_Init();                           // Reloj del sistema => 50MHz
  InicializaNokia5110();
  ConfigPtoSerial();

  while(1){
      //////////////////// VALORES INICIALES ///////////////////////////////
      ///se borran los datos del arreglo escenario
      for(i=0;i<504;i++){
          escenario[i]=0;
      }
      GenerarMapa(map);
      j1.x=1;
      j1.y=1;
      j1.cantbomb=1;
      j1.RangBomb=1;
      j1.vida=1;
      j1.puntaje = 0;
      j2.x=19;
      j2.y=9;
      j2.cantbomb=1;
      j2.RangBomb=1;
      j2.vida=1;
      j2.puntaje = 0;
      i=0;

      ////////////////////PANTALLA DE INICIO////////////////////////
      do{
          PWM1_ENABLE_R |= (PWM_ENABLE_PWM0EN);
          if(conteoFrecuencia == Delay) {
              PlayBackgroundMusic(&FrecuenciaActual);
              conteoFrecuencia = 0;
          }else {conteoFrecuencia++;}
          ////MostrarPantalladeInicio
          if(i==2083334)
              i=0;
          if(i==0)
              PintarPantallaconst(juegoinicio);
          if(i==1041667)
              PintarPantallaconst(juegoinicio2);
          i++;
      }while(!(SondeaTecla(&datoRx)));
      PWM1_ENABLE_R &= ~(PWM_ENABLE_PWM0EN);
      Retardo(4000);
      ConfigTemporizador250ms();
      temp=0;

      //////////////////JUEGO//////////////////////
     while(temp<720 && j1.vida ==1 && j2.vida ==1){ //720 = 3 min
      //Valida acciones del jugador
      if(SondeaTecla(&datoRx)){
          j1 = ValidarMovJugador(datoRx,j1,1,map,escenario);
          j2 = ValidarMovJugador(datoRx,j2,2,map,escenario);
          ValidarExplosion(datoRx,map,Bomba,&j1,&j2,BombasActivas);
          if(datoRx=='p'){ //pausa
              while(!SondeaTecla(&datoRx));
          }
      }
      if(ValidarFinTemporizador250ms()==1){
          temp++;
      }

      j1 = AplicarPowerUp(map, j1);
      j2 = AplicarPowerUp(map, j2);
      ValidarExplosion(0,map,Bomba,&j1,&j2,BombasActivas);

      //Sonido de la explosion
      if(condicion-1 == BombasActivas[0]+BombasActivas[1]){
          explosion = 1;
      }
      condicion = BombasActivas[0]+BombasActivas[1];

      if(explosion == 1){
          PWM1_ENABLE_R |= (PWM_ENABLE_PWM0EN);
          PlayBomb();
          tempInicial = temp;
          explosion = 0;
      }
      if((temp-tempInicial) ==  3){
          PWM1_ENABLE_R &= ~(PWM_ENABLE_PWM0EN);
          tempInicial = 0;
      }

      //Pintar escenario
      Pintarescenario(map,escenario);
      PintarJugador(j1,1,escenario,1);
      PintarJugador(j2,2,escenario,1);
      PintarTiempo(temp,escenario);
      PintarPantalla(escenario);
      if(ValidarFinTemporizador250ms()==1){
          temp++;
      }
      Retardo(16666667/20); // 50ms

      /////////////////////////// FIN DE LA PARTIDA ////////////////////////////////////////////////////////
      if(temp==720 || j1.vida == 0 || j2.vida ==0){
          BorrarPantalla();
          PWM1_ENABLE_R &= ~(PWM_ENABLE_PWM0EN);
         if(j1.vida == 1 && j2.vida ==1){
              if(j1.puntaje== j2.puntaje){
                  EscribirCadena("************   Empate   ************ Puntaje:   ************************"  );
                  PonerCursor(9,3);
                  EscribirNumero(j1.puntaje);
              }
              if(j1.puntaje > j2.puntaje){
                  EscribirCadena("************  J1 gana   ************ Puntaje:   ************************"  );
                  PonerCursor(9,3);
                  EscribirNumero(j1.puntaje);
              }else{
                  EscribirCadena("************  J2 gana   ************ Puntaje:    ************************"  );
                  PonerCursor(9,3);
                  EscribirNumero(j2.puntaje);
              }
         }else{
             if(j2.vida==0 && j1.vida==1){
                 EscribirCadena("************   Empate   ************************************************"  );
             }
             if(j2.vida==0 && j1.vida==1){
                 EscribirCadena("************  J1 gana   ************ Puntaje:   ************************"  );
                 PonerCursor(9,3);
                 EscribirNumero(j1.puntaje);
             }
             if(j1.vida==0 && j2.vida==1){
                 EscribirCadena("************  J2 gana   ************ Puntaje:    ************************"  );
                 PonerCursor(9,3);
                 EscribirNumero(j2.puntaje);
             }
         }
          Retardo(16666667);// 3seg;
          VaciarBufferRx(datoRx);
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////
      }

    }
  }
}
