# Pico MIDI Keyboard
Firmware de controlador MIDI para o Raspberry Pi Pico  
Guia disponível em: [:brazil:](/assets/readmes/pt-br.md), [:us:](README.md)
![Configuração padrão](/assets/pinout.png "Configuração padrão da placa")
## Montando o projeto
Se você não tem o SDK do pico instalado, execute os seguintes comandos *(não se esqueça de trocar ```<PATH-TO-PICO-SDK>``` pelo caminho do seu SDK):
```
$ git clone https://github.com/raspberrypi/pico-sdk.git --branch master
$ cd pico-sdk
$ git submodule update --init
$ cd ..
$ export PICO_SDK_PATH=<PATH-TO-PICO-SDK>
```
Em seguida, execute os seguintes comandos para montar o projeto
```
$ git clone https://github.com/LucasCalcada/PicoMIDIKeyboard
$ cd PicoMIDIKeyboard
$ mkdir build
$ cd build
$ cmake ..
$ make
```
## Instalação
Você pode baixar uma versão já montada na seção [releases](https://github.com/LucasCalcada/PicoMIDIKeyboard/releases/latest)
***(É recomendado montar o projeto você mesmo, já que você pode customizar as configurações de acordo com suas necessidades)***  
O firmware pode ser instalado ao segurar o botão BOOTSEL da placa e copiando o arquivo MIDIKeyboard.uf2 para o armazenamento interno da placa.
## Configuração
Ao editar o arquivo *midi_config.h* você pode customizar a funcionalidade do teclado
| Opção | Descrição |
|--------|-------------|
| PINS[ ] | Define quais pinos serão usados como teclas |
| NOTES[ ] | Define quais notas cada pino enviará |
| OCTAVE_AMMOUNT | Define quantas oitavas serão usadas (depende da quantidade de pinos definida) | 
| INITIAL_OCTAVE_OFFSET | Define o offset de oitavas inicial |
| OCTAVE_UP and OCTAVE_DOWN | Define os pinos usados para os botões de aumentar e diminuir o offset |