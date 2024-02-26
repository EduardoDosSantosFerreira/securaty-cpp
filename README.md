# Sistema de Controle de Acesso com Arduino em C++

![Securaty](https://github.com/EduardoDosSantosFerreira/securaty-cpp/blob/main/securaty.png)

O código fornecido implementa um sistema de controle de acesso utilizando um teclado, um display LCD, um LED, um buzzer e um servomotor. O sistema permite que o usuário insira uma senha no teclado para destravar o acesso.

## Componentes Utilizados

- Arduino board
- Teclado (keypad)
- Display LCD
- LED (vermelho e verde)
- Buzzer
- Servomotor
- Memória EEPROM (para armazenar a senha)

## Funcionalidades do Sistema

1. **Entrada de Senha**

   - Um teclado é utilizado para inserir a senha de acesso.
   - O display LCD mostra os dígitos digitados.

2. **Controle do Servomotor**

   - O servomotor é utilizado para trancar e destrancar o acesso conforme o estado do sistema.

3. **Feedback Visual e Sonoro**

   - LEDs indicam se o acesso está travado (LED vermelho) ou destravado (LED verde).
   - Um buzzer emite sons para indicar ações ou alertas, como a entrada de dígitos ou a confirmação de uma ação.

4. **Armazenamento da Senha**

   - A senha de acesso é armazenada na memória EEPROM do Arduino.

5. **Redefinição da Senha**

   - Existe a possibilidade de redefinir a senha através de um procedimento específico.

## Implementação em C++

O código em C++ implementa a lógica para receber a senha do teclado, verificar se a senha está correta, destravar o acesso quando a senha é correta, além de permitir a redefinição da senha. Além disso, o código controla a ativação do servomotor, a exibição de informações no display LCD e a geração de sons pelo buzzer.

## Considerações Finais

O sistema de controle de acesso em Arduino oferece uma solução prática e customizável para implementar um sistema de segurança simples. Sua flexibilidade permite a integração de diferentes componentes e funcionalidades para atender às necessidades específicas de controle de acesso e segurança.
