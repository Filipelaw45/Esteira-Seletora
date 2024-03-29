#include <Arduino.h>

// acho q tem algum pino analógico confirma com o professor

#define SC 0
#define SI 1
#define SA 2
#define SM 3
#define SB 4
#define SD 5
#define SSB 6
#define SSM 7
#define SSA 8
#define A1 9
#define A2 10
#define A3 11

//trocar os dois pinos abaixo de chave seletora e de chave de liga/desliga
// para a que o professor colocou no arduino
#define CHL 12
#define CHS 13

int qtdPecasMetalicas = 0;
int qtdPecasPlasticas = 0;
int qtdPecasMetalRejeitadas = 0;
int qtdPecasPlastRejeitadas = 0;
int qtdPecasSelecionadas = 0;
int qtdPecasRejeitadas = 0;

String peca = "";

int calcTotal(int a, int b) { return a + b; };

void ativarPistao(int pin) { digitalWrite(pin, HIGH); };

void desativarPistao(int pin) { digitalWrite(pin, LOW); };

// bool chavePlastico() { return (digitalRead(CHS) == LOW && peca == "plastico"); };

// bool chaveMetal() { return (digitalRead(CHS) == HIGH && peca == "metal"); };

void contarPeca(String peca) {
    if (digitalRead(SSA) || digitalRead(SSM) || !digitalRead(SSB) || digitalRead(SD)){

        if (peca == "metal" && !digitalRead(SD)) qtdPecasMetalicas++;
        if (peca == "plastico" && !digitalRead(SD)) qtdPecasPlasticas++;

        if (peca == "metal" && digitalRead(SD)) qtdPecasMetalRejeitadas++;
        if (peca == "plastico" && digitalRead(SD)) qtdPecasPlastRejeitadas++;

        qtdPecasSelecionadas = calcTotal(qtdPecasMetalicas, qtdPecasPlasticas);
        qtdPecasRejeitadas = calcTotal(qtdPecasMetalRejeitadas, qtdPecasPlastRejeitadas);

        Serial.print("\nmetal Selecionada = " + String(qtdPecasMetalicas));
        Serial.print("\nplastico Selecionada = " + String(qtdPecasPlasticas));
        Serial.print("\ntotal Selecionada = " + String(qtdPecasSelecionadas));
        Serial.print("\n----------------------------");
        Serial.print("\nmetal Rejeitada = " + String(qtdPecasMetalRejeitadas));
        Serial.print("\nplastico Rejeitada = " + String(qtdPecasPlastRejeitadas));
        Serial.print("\ntotal Rejeitada = " + String(qtdPecasRejeitadas));
        Serial.print("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
        delay(150);
    }
}

void filtroTamanho() {
      
    if (digitalRead(SA)) ativarPistao(A1);
    if (digitalRead(SSA))desativarPistao(A1);

    if (digitalRead(SM)) ativarPistao(A2);
    if (digitalRead(SSM)) desativarPistao(A2);

    if (digitalRead(SB)) ativarPistao(A3);
    if (!digitalRead(SSB)) desativarPistao(A3);
}

void setup() {
    Serial.begin(9600);

    pinMode(SC, INPUT);
    pinMode(SI, INPUT);
    pinMode(SA, INPUT);
    pinMode(SM, INPUT);
    pinMode(SB, INPUT);
    pinMode(SD, INPUT);
    pinMode(SSB, INPUT);
    pinMode(SSM, INPUT);
    pinMode(SSA, INPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(CHL, INPUT);
    pinMode(CHS, INPUT);

    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);

}

void loop() {
    
    if(digitalRead(CHS) == HIGH && digitalRead(SC) == HIGH && digitalRead(SI) == HIGH){
        peca = "metal";
    }

    if(digitalRead(CHS) == LOW && digitalRead(SC) == HIGH && digitalRead(SI) == LOW){
        peca = "plastico";
    }

    if(digitalRead(SSA) || digitalRead(SSM) || digitalRead(SSB) || digitalRead(SD)){
        saiu = true;
    }


    if (digitalRead(CHL)) {  
            
        if (peca == "metal" || peca == "plastico"){
            while(!saiu){
                filtroTamanho();
            }
        }
        
        contarPeca(peca);
        
    }
}
