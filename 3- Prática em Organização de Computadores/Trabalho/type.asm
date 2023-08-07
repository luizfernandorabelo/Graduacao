jmp Main

; Dados da palavra atual:
corAtualdaPalavra: var #1
palavraAtual: var #10
posAtualdaPalavra: var #1

posPalavraCaractere1: var #1
    static posPalavraCaractere1 + #0, #16

; Nro de palavras que o usuário já acertou:
nPalavrasResolvidas: var #1
static nPalavrasResolvidas + #0, #0

; Nro de letras acertadas da palavra atual e última letra digitada:
nLetrasDeletadas: var #1
letraDigitada: var #1

; Dados do tiro:
posTiro: var #1
flagTiro: var #1
corTiro: var #1


Main:

    ; Imprimindo a tela inicial do jogo por 1s:
    loadn r1, #tela1Linha0      ; endereço de início da tela inicial
    loadn r2, #2304             ; cor vermelha para nome do jogo 
    call ImprimeTela
    call DelayFixo
    call ApagaTela

    ; Imprimindo a tela com a nave:
    loadn r1, #tela2Linha0      ; endereço inicial da tela da nave
    loadn r2, #1280             ; cor roxa para nave
    call ImprimeTela

    ; Inicializando a cor atual da palavra:
    loadn r1, #2560             ; cor verde lima
    store corAtualdaPalavra, r1

    ; Inicializando os dados do tiro:
    loadn r0, #0                
    loadn r1, #25               
    loadn r2, #2816
    store posTiro, r1           ; altura 25 = altura da tela - altura da nave
    store flagTiro, r0          ; falso
    store corTiro, r2           ; cor amarela

    ; Inicializando registradores auxiliares:
    loadn r3, #0                ; contador de palavras
    loadn r6, #palavra1         ; endereço inicial da primeira palavra
    loadn r4, #10               ; valor para pular para a próxima palavra na memória
    loadn r5, #24               ; número máximo de palavras

    Main_Loop:

        ; Atualizando a palavra atual na memória:
        mov r1, r6
        call MudaPalavraAtual

        ; Imprimindo a palavra atual:
        loadn r1, #palavraAtual         ; pega a palavraAtual
        load r0, posPalavraCaractere1   ; posição para impressão na tela
        load r2, corAtualdaPalavra      ; resgata a cor para impressão na tela
        call ImprimeStr
        call DelayFixo

        ; Movendo a palavra verticalmente:
        call MovePalavra

        ; Incrementando o número de palavas resolvidas:
        load r0, nPalavrasResolvidas
        inc r0
        store nPalavrasResolvidas, r0

        ; Verificando se chegou no fim do jogo:
        cmp r3, r5
        ceq FimDoJogo_Ganhou

        ; Se não, repetindo Main_Loop:
        inc r3
        add r6, r6, r4
        jmp Main_Loop

	halt ; nunca vai chegar aqui


ImprimeTela:    ; Função que imprime a tela inteira de um cenário         
                ; Parâmetros: r1 -> endereço da primeira linha do cenário 
                ;             r2 -> cor do cenário a ser impresso         

    ; Protegendo os conteúdos dos registradores:
    push r0	
    push r1	
    push r2	
    push r3	
    push r4	
    push r5	

    loadn R0, #0        ; começo da tela
    loadn R3, #40       ; incremento da posição da tela
    loadn R4, #41       ; incremento do ponteiro das linhas da tela
    loadn R5, #1200     ; limite da tela (largura x altura)

    ImprimeTela_Loop:
        call ImprimeStr
        add r0, r0, r3       ; incrementa posicão para a próxima linha na tela (r0 += 40)
        add r1, r1, r4       ; incrementa o ponteiro para o comeco da proxima linha na memória (r1 += 41), 41 por causa do '\0'
        cmp r0, r5           ; Compara r0 com 1200
        jne ImprimeTela_Loop ; while (r0 < 1200), continua no loop

    ; Recuperando os conteúdos dos registradores:
    pop r5	
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0

    rts ; return


ImprimeStr:     ; Função que imprime uma mensagem na tela até encontrar o '\0'                           
                ; Parâmetros: r0 -> posição da tela em que o primeiro caractere da mensagem será impresso
                ;             r1 -> endereço da mensagem                                                 
                ;             r2 -> cor da mensagem                                                      

    ; Protegendo os conteúdos dos registradores:
    push r0	
    push r1	
    push r2	
    push r3	
    push r4	

    loadn r3, #'\0'	; critério de parada = '\0'

    ; Imprimindo a string:
    ImprimeStr_Loop:	
        loadi r4, r1        ; obtém o charAtual da string
        cmp r4, r3		   	; if (charAtual == '\0'), vai embora
        jeq ImprimeStr_Sai
        add r4, r2, r4		; soma a cor
        outchar r4, r0		; imprime o caractere na tela
        inc r0				; incrementa a posicao na tela
        inc r1				; incrementa o ponteiro da String
        jmp ImprimeStr_Loop
	
    ; Recuperando os conteúdos dos registradores:
    ImprimeStr_Sai:	
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0

    rts ; return


DelayFixo:      ; Função que pausa a execução do programa em um tempo fixo (aprox 1s)

    ; Protegendo o conteúdo dos registradores:
    push r0
    push r1
    push r2

    loadn r1, #200
    loadn r2, #0
    Delay_volta2:
        loadn r0, #40000
        Delay_volta: 
            dec r0
            cmp r0, r2					
            jnz Delay_volta	
        dec r1
        cmp r1, r2
        jnz Delay_volta2

    ; Recuperando o valor anterior dos registradores:
    pop r2
    pop r1
    pop r0

    rts ; return


ApagaTela:      ; Função que apaga a tela inteira, preenchendo-a com espaços (' ')

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1
    push r2

    ; Carregando constantes:
    loadn r0, #1200         ; total de posicoes da tela
    loadn r1, #' '          ; 32 (ASCII espaço)
    loadn r2, #0            ; valor inteiro 0

    ; Loop (r0=1200; r0>=0;  r0--)
    ApagaTela_Loop:	    
        dec r0              ; r0--
        outchar r1, r0      ; preenche espaço
        cmp r0, r2
        jnz ApagaTela_Loop
 
    ; Recuperando os valores anteriores dos registradores:
    pop r2
    pop r1
    pop r0

    rts ; return


MudaCorPalavra:     ; Função que muda a cor da palavra

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1
    push r2

    ; Carregando os códigos das cores:
    loadn r0, #0000 	; cor branca
    loadn r1, #2560		; cor verde lima

    load r2, corAtualdaPalavra		    ; r2 = corAtualdaPalavra

    ; Se cor for branca, corAtual vai de branco -> lima / se não corAtual vai de lima -> branco
    cmp r2, r0
    jeq MudaCorBranca

    MudaCorLima:
        store corAtualdaPalavra, r0     ; muda da cor Lima para branca 
        jmp fimMudaCor
    MudaCorBranca:
        store corAtualdaPalavra, r1     ; muda da cor branca para lima
    fimMudaCor:

    ; Recuperando os conteúdos dos registradores:
    pop r2
    pop r1
    pop r0

    rts	; return


MudaPalavraAtual:       ; Função que altera a palavra atual
                        ; Parâmetro: r1 -> endereço inicial para a nova palavra

    ; Protegendo os conteúdos dos registradores: 
    push r0
    push r1
    push r2
    push r3
    push r5

    call Atualiza_score

    ; Mudando a cor da palavra (volta a ser branca):
    call MudaCorPalavra	

    ; Obtendo o endereço da variável palavra atual:
    loadn r0, #palavraAtual     ; r0 = endereço do 1° byte de palavraAtual

    ; Inicializando registradores auxiliares para o loop:
    loadn r2, #9               ; tamanho total da string
    loadn r3, #0                ; contador para escrever a palavra

    ; Resetando a posição e o número de letras digitadas para 0:
    store posAtualdaPalavra, r3
    store nLetrasDeletadas, r3

    ; Percorrendo loop que modifica a palavra atual, resgatando cada letra da memória e colocando na variável palavraAtual:
    MudaPalavraAtual_Loop:
        loadi r5, r1            ; r5 = charAtual da nova palavra
        storei r0, r5           ; guarda o charAtual da nova palavra na palavraAtual
        inc r0                  ; incrementa o endereço de palavraAtual
        inc r1                  ; incrementa o endereço da nova palavra
        inc r3                  ; incrementa contador
        cmp r3, r2              ; if (contador <= tamanhoPalavra), continua no loop
        jle MudaPalavraAtual_Loop

    ; Adicionando o terminador de string '\0' na palavra:
    loadn r3, #'\0'				
    storei r0, r3

    ; Recuperando os conteúdos dos registradores:
    pop r5
    pop r3
    pop r2
    pop r1
    pop r0

    rts ; return


MovePalavra:

    ; Protegendo os conteúdos dos registradores:
    push r5
    push r6
    push r0
    push r1
    push r2
    push r3
    push r4

    loadn r5, #0                    ; contador para o MovePalavra for (int r5 = 0; r5 < r6; r5++)
    loadn r6, #25                   ; linha limite onde a palavra pode chegar

	MovePalavra_Loop:

        ; Calculando o endereço da letra certa para resgatar a letra esperada:
        loadn r0, #palavraAtual	
        loadn r1, #0
        load r2, nLetrasDeletadas
        add r0, r0, r1
        add r0, r0, r2
        loadi r1, r0            ; r1 tem a letra esperada

        ; Movendo a palavra 1 linha para baixo:
        call MovePalavra_Redesenha

        ; Verificando letra retornada pela DigLetra:
        call DigLetra
        load r2, letraDigitada  ; resgata a letra digitada

        ; Deletando uma letra se o usuário digitou a letra esperada:
        cmp r1, r2              ; if(r1 == r2) then DeletaLetra, r1 = letra esperada, r2 = letra digitada (ou 255)
        ceq DeletaLetra

        ; Movendo o tiro:
        call MoveTiro

        ; Verificando se a palavra já está resolvida:
        load r3, nLetrasDeletadas   ; verifica se todas as letras já foram deletadas
        loadn r4, #9
        cmp r3, r4
        jeq fimMovepalavra          ; caso todas as letras foram deletadas, sai do loop interno

        ; Verificando se o usuário perdeu:
        inc r5
        cmp r5, r6                  ; enquanto não chegou na ultima linha, volta para o loop
        jne MovePalavra_Loop
        call FimDoJogo_Perdeu       ; caso a palavra chegou no limite da última linha, a pessoa perde o jogo
	fimMovepalavra:

    call MovePalavra_Redesenha      ; apaga o último caractere da palavra

    ; Recuperando os conteúdos dos registradores:
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0
    pop r6
    pop r5

    rts ; return


MovePalavra_Redesenha:      ; função que redesenha a palavra no vídeo

    ; Proteção de dados dos registradores
    push r0
    push r2
    push r4		
    push r1
    push r3

    load r0, posAtualdaPalavra
    load r3, posPalavraCaractere1

    push r0

    ; Apagando palavra atual da tela:
    loadn r4, #40           ; r4 = 40 = largura da tela
    mul r0, r0, r4          ; r0 *= r4 (posicão inicial para imprimir na tela)
    loadn r1, #tela0Linha0  ; endereço inicial de uma linha vazia
    loadn r2, #3840         ; cor preta para a deleção
    call ImprimeStr

    pop r0					

    ; Incrementando a posição atual da palavra:
    inc r0
    store posAtualdaPalavra, r0

    ; Imprimindo a palavra:
    mul r0, r0, r4              ; r0 *= r4 (posição da palavra)
    add r0, r0, r3              ; r0 += 16 posicao da palavra
    loadn r1, #palavraAtual     ; endereço da palavra atual
    load r2, corAtualdaPalavra  ; cor da palavra atual 
    call ImprimeStr

    ; Recuperando os dados dos registradores:
    pop r3
    pop r1
    pop r4
    pop r2
    pop r0

    rts	; return


DeletaLetra:        ; Função que deleta a letra da palavra atual
                    ; Parâmetro: r0 -> endereço da da letra a ser deletada

    ; Protegendo o conteúdo dos registradores
    push r0
    push r1
    push r2

    ; Modificando a letra na memória, substituindo com espaço:
    loadn r1, #' '				; caractere espaço ' ' (ASCII = 32)
    storei r0, r1

    ; Incrementando o número de letras deletadas na memória:
    load r2, nLetrasDeletadas
    inc r2
    store nLetrasDeletadas, r2

    ; Mudando a cor da palavra se ela ainda estiver branca:
    load r1, corAtualdaPalavra
    loadn r2, #0000
    cmp r1, r2
    ceq MudaCorPalavra

    ; Acionando a flag de tiro:
    loadn r0, #1
    store flagTiro, r0

    ; Recuperando o conteúdo dos registradores:
    pop r2
    pop r1
    pop r0

    rts ; return


DigLetra:   ; Espera que uma tecla seja digitada e salva na variavel global "Letra"

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1

    ; Leitura:
    inchar r0						; Lê o teclado, se nada for digitado, letraDigitada = 255
    store letraDigitada, r0			; Salva a tecla na variavel global "letraDigitada"

    ; Recuperando os conteúdos dos registradores:
    pop r1
    pop r0

    rts ; return


MoveTiro:       ; Função que move o tiro na tela, pausando a execução do programa em um tempo variável

    ; Protegendo o conteúdo dos registradores:
    push r0
    push r1
    push r2
    push r3
    push r4

    ; r0 = Δt da pausa = (25 - nPalavrasResolvidas) * 12800
    load r4, nPalavrasResolvidas 
    loadn r0, #25                
    sub r0, r0, r4               
    loadn r4, #22000               
    mul r0, r0, r4

    ; Inicializando demais registradores para o loop:
    loadn r1, #25				; 25 para o "laço" do delay
    loadn r2, #0                ; contador para o delay

    ; Reposicionando o tiro na posição inicial:
    store posTiro, r1

    MoveTiro_Delay2:
        mov r3, r0
        MoveTiro_Delay: 
            dec r3
            cmp r3, r2					
            jnz MoveTiro_Delay
        dec r1
        call MoveTiro_Redesenha
        cmp r1, r2
        jnz MoveTiro_Delay2

    ; Recuperando o valor anterior dos registradores:
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0

    rts ; return


MoveTiro_Redesenha:

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5

    ; Skipando se a flag de tiro for 0:
    load r1, flagTiro
    loadn r2, #0
    cmp r1, r2
    jeq MoveTiro_Redesenha_Skip

    ; Obtendo a posição do tiro da memória:
    load r0, posTiro

    ; Obtendo o número da posição do tiro na tela (posTiro * 40 + 20)
    loadn r1, #40
    loadn r2, #20
    mul r1, r1, r0
    add r1, r1, r2

    ; Apagando o tiro com espaço:
    loadn r3, #' '
    outchar r3, r1

    ; Verificando se o tiro vai colidir com a palavra:
    load r4, posAtualdaPalavra
    inc r4
    cmp r0, r4
    jeq MoveTiro_Redesenha_Colisao

    ; Obtendo a nova posição do tiro na tela (posTiro * 40 + 20 - 40):
    loadn r2, #40
    sub r1, r1, r2

    ; Reescrevendo o tiro:
    loadn r3, #'|'
    load r4, corTiro
    add r3, r3, r4
    outchar r3, r1

    ; Decrementando a posição do tiro:
    dec r0
    store posTiro, r0
    
    jmp MoveTiro_Redesenha_Skip

    MoveTiro_Redesenha_Colisao:
        ; Negando a flag de tiro:
        loadn r0, #0
        store flagTiro, r0

    MoveTiro_Redesenha_Skip:
        ; Recuperando os conteúdos dos registradores:
        pop r5
        pop r4
        pop r3
        pop r2
        pop r1
        pop r0

    rts ; return


FimDoJogo_Perdeu:   ; Função para imprimir a tela "VOCÊ PERDEU!!!"

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5
    push r6

    call ApagaTela

    ; Calculando o endereço para adicionar o número de palavras resolvidas na tela:
    loadn r1, #30                   ; r3 = 30 (posição no eixo x da pontuação)
    loadn r2, #tela4Linha13         ; linha da tela da pontuação
    add r2, r2, r1                  ; posição em que a pontuação deve ser adicionada

    loadn r6, #'0'                  ; adicionando o número de palavras resolvidas na tela ;
    load r3, nPalavrasResolvidas
    loadn r4, #10
    div r5, r3, r4                  ; r5 = r3/r4 -> r5 recebe o decimal
    mod r3, r3, r4                  ; r3 = r3 % r4 -> r3 recebe a unidade

    add r5, r5, r6                  ; r5 += '0'
    add r3, r3, r6                  ; r3 += '0'
    storei r2, r5                   ; substitui o número na tela
    inc r2
    storei r2, r3 

    loadn r0, #0
    loadn r1, #tela4Linha0          ; endereço inicial da tela
    loadn r2, #2304                 ; cor vermelha para impressão da tela

    call ImprimeTela

    ; Recuperando os conteúdos dos registradores:
    pop r6
    pop r5
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0

    jmp paraExecucao


FimDoJogo_Ganhou:   ; Função que printa a tela "VOCÊ GANHOU!!!!"

    ; Protegendo os conteúdos dos registradores:
    push r0
    push r1
    push r2

    call ApagaTela

    loadn r0, #0                ; posição inicial para imprimir a tela 
    loadn r1, #tela3Linha0      ; endereço inicial para impressão da tela
    loadn r2, #0768             ; cor verde oliva para impressão da tela 

    call ImprimeTela

    ; Recuperando os conteúdos dos registradores:
    pop r2
    pop r1
    pop r0

    rts ; return

Atualiza_score:                 ; função que atualiza o score na tela

    push r0
    push r1
    push r2
    push r3
    push r4

    load r0, nPalavrasResolvidas        ; r0 = nPalavrasResolvidas
    loadn r1, #10                       ; r1 = 10

    mod r2, r0, r1                      ; r2 = r0 % r1      -> digito unitário de r0
    div r3, r0, r1                      ; r3 = r0 // r1   -> digito decimal de r0

    loadn r4, #'0'             ; caractere '0' para ajuste de caractere

    add r2, r2, r4             ; ajustando o caractere para impressão na tela             
    add r3, r3, r4             ; ajustando o caractere para impressão na tela

    loadn r4, #1280            ; cor roxa para impressão do score

    add r2, r2, r4             ; atualizando r2 com a cor roxa
    add r3, r3, r4             ; atualizando r3 com a cor roxa

    loadn r0, #1156            ; r0 = posição exata para escrever o score             

    outchar r3, r0

    inc r0

    outchar r2, r0

    pop r4
    pop r3
    pop r2
    pop r1
    pop r0

    rts


paraExecucao:       ; Função para parar a execução do jogo
	halt


; TELA 0 = tela vazia
tela0Linha0  : string "                                        "
tela0Linha1  : string "                                        "
tela0Linha2  : string "                                        "
tela0Linha3  : string "                                        "
tela0Linha4  : string "                                        "
tela0Linha5  : string "                                        "
tela0Linha6  : string "                                        "
tela0Linha7  : string "                                        "
tela0Linha8  : string "                                        "
tela0Linha9  : string "                                        "
tela0Linha10 : string "                                        "
tela0Linha11 : string "                                        "
tela0Linha12 : string "                                        "
tela0Linha13 : string "                                        "
tela0Linha14 : string "                                        "
tela0Linha15 : string "                                        "
tela0Linha16 : string "                                        "
tela0Linha17 : string "                                        "
tela0Linha18 : string "                                        "
tela0Linha19 : string "                                        "
tela0Linha20 : string "                                        "
tela0Linha21 : string "                                        "
tela0Linha22 : string "                                        "
tela0Linha23 : string "                                        "
tela0Linha24 : string "                                        "
tela0Linha25 : string "                                        "
tela0Linha26 : string "                                        "
tela0Linha27 : string "                                        "
tela0Linha28 : string "                                        "
tela0Linha29 : string "                                        "


; TELA 1 = tela inicial do joguinho
tela1Linha0  : string "                                        "
tela1Linha1  : string "                                        "
tela1Linha2  : string "                                        "
tela1Linha3  : string "                                        "
tela1Linha4  : string "    ._____.   __    __   _____ _____    "
tela1Linha5  : string "    |_   _|   \\ \\  / /  || * | |____|   "
tela1Linha6  : string "      | |      \\ \\/ /   ||---- |____    "
tela1Linha7  : string "      | |       |   |   ||     |____|   "
tela1Linha8  : string "      | |       |   |   ||     |____    "
tela1Linha9  : string "      |_|       |___|   ||     |____|   "
tela1Linha10 : string "                                        "
tela1Linha11 : string "                                        "
tela1Linha12 : string "       ._____.  _     _   _____         "
tela1Linha13 : string "       |_   _| | |   | |  |____|        "
tela1Linha14 : string "         | |   | |___| |  |____         "
tela1Linha15 : string "         | |   |  ___  |  |____|        "
tela1Linha16 : string "         | |   | |   | |  |____         "
tela1Linha17 : string "         |_|   |_|   |_|  |____|        "
tela1Linha18 : string "                                        "
tela1Linha19 : string "                                        "
tela1Linha20 : string "   ___             __    __.  ______    "
tela1Linha21 : string "  //__|     /\\     | \\  /  |  |_____|   "
tela1Linha22 : string " //  __    /  \\    |  \\/   |  |_____    "
tela1Linha23 : string " || |__|  / /\\ \\   | |\\_/| |  |_____|   "
tela1Linha24 : string " ||  //  / /  \\ \\  | |   | |  |_____    "
tela1Linha25 : string "  \\_//  /_/    \\_\\ |_|   |_|  |_____|   "
tela1Linha26 : string "                                        "
tela1Linha27 : string "                                        "
tela1Linha28 : string "                                        "
tela1Linha29 : string "                                        "


; TELA 2 = Nave Sozinha
tela2Linha0  : string "                                        "
tela2Linha1  : string "                                        "
tela2Linha2  : string "                                        "
tela2Linha3  : string "                                        "
tela2Linha4  : string "                                        "
tela2Linha5  : string "                                        "
tela2Linha6  : string "                                        "
tela2Linha7  : string "                                        "
tela2Linha8  : string "                                        "
tela2Linha9  : string "                                        "
tela2Linha10 : string "                                        "
tela2Linha11 : string "                                        "
tela2Linha12 : string "                                        "
tela2Linha13 : string "                                        "
tela2Linha14 : string "                                        "
tela2Linha15 : string "                                        "
tela2Linha16 : string "                                        "
tela2Linha17 : string "                                        "
tela2Linha18 : string "                                        "
tela2Linha19 : string "                                        "
tela2Linha20 : string "                                        "
tela2Linha21 : string "                                        "
tela2Linha22 : string "                                        "
tela2Linha23 : string "                                        "
tela2Linha24 : string "                                        "
tela2Linha25 : string "                                        "
tela2Linha26 : string "                    /\\                  "
tela2Linha27 : string "                   /  \\                 "
tela2Linha28 : string "                  |^  ^|    score : 00  "
tela2Linha29 : string "                  |____|                "


; TELA 3: tela de fim de jogo (GANHOU)
tela3Linha0  : string "                                        "
tela3Linha1  : string "                                        "
tela3Linha2  : string "                                        "
tela3Linha3  : string "                                        "
tela3Linha4  : string "                                        "
tela3Linha5  : string "                                        "
tela3Linha6  : string "                                        "
tela3Linha7  : string "       ._________________________.      "
tela3Linha8  : string "       |*************************|      "
tela3Linha9  : string "       |*                       *|      "
tela3Linha10 : string "       |*    P A R A B E N S    *|      "
tela3Linha11 : string "       |* V O C E   G A N H O U *|      "
tela3Linha12 : string "       |*                       *|      "
tela3Linha13 : string "       |*************************|      "
tela3Linha14 : string "       |_________________________|      "
tela3Linha15 : string "                                        "
tela3Linha16 : string "                                        "
tela3Linha17 : string "                                        "
tela3Linha18 : string "                                        "
tela3Linha19 : string "                                        "
tela3Linha20 : string "                                        "
tela3Linha21 : string "                                        "
tela3Linha22 : string "                                        "
tela3Linha23 : string "                                        "
tela3Linha24 : string "                                        "
tela3Linha25 : string "                                        "
tela3Linha26 : string "                                        "
tela3Linha27 : string "                                        "
tela3Linha28 : string "                                        "
tela3Linha29 : string "                                        "


; TELA 4: tela de fim de jogo (PERDEU)
tela4Linha0  : string "                                        "
tela4Linha1  : string "                                        "
tela4Linha2  : string "                                        "
tela4Linha3  : string "                                        "
tela4Linha4  : string "                                        "
tela4Linha5  : string "                                        "
tela4Linha6  : string "                                        "
tela4Linha7  : string "       ._________________________.      "
tela4Linha8  : string "       |                         |      "
tela4Linha9  : string "       |                         |      "
tela4Linha10 : string "       |  V O C E   P E R D E U  |      "
tela4Linha11 : string "       |                         |      "
tela4Linha12 : string "       |                         |      "
tela4Linha13 : string "       | No PALAVRAS CERTAS : XX |      "
tela4Linha14 : string "       |                         |      "
tela4Linha15 : string "       |_________________________|      "
tela4Linha16 : string "                                        "
tela4Linha17 : string "                                        "
tela4Linha18 : string "                                        "
tela4Linha19 : string "                                        "
tela4Linha20 : string "                                        "
tela4Linha21 : string "                                        "
tela4Linha22 : string "                                        "
tela4Linha23 : string "                                        "
tela4Linha24 : string "                                        "
tela4Linha25 : string "                                        "
tela4Linha26 : string "                                        "
tela4Linha27 : string "                                        "
tela4Linha28 : string "                                        "
tela4Linha29 : string "                                        "


; palavras para o usuário digitar 
palavra1  : string "ambiguous"
palavra2  : string "automatic"
palavra3  : string "available"
palavra4  : string "catalogue"
palavra5  : string "chocolate"
palavra6  : string "criticism"
palavra7  : string "detective"
palavra8  : string "economics"
palavra9  : string "effective"
palavra10 : string "essential"
palavra11 : string "formation"
palavra12 : string "intention"
palavra13 : string "invisible"
palavra14 : string "modernize"
palavra15 : string "parameter"
palavra16 : string "performer"
palavra17 : string "policeman"
palavra18 : string "practical"
palavra19 : string "president"
palavra20 : string "privilege"
palavra21 : string "secretary"
palavra22 : string "situation"
palavra23 : string "strategic"
palavra24 : string "treatment"
palavra25 : string "vegetable"
