.data
    .align 2
        integer1: .word 25   # armazenando um int32 na memória
        integer2: .word 75   # armazenando um int32 na memória

.text
    .globl main              # criando rótulo global para ponto de entrada do programa
    
    main:
        # Adicionando inteiros quaisquer:
        li $t0, 25           # carregando valor 25 para o registrador $t0
        li $t1, 75           # carregando o valor 75 para o registrador $t1
        add $s0, $t0, $t1    # guardando a soma dos conteúdos de $t0 e $t1 em $s0
        
        # Adicionando inteiros vindos da memória:
        lw $t2, integer1     # carregando o conteúdo de integer1 para $t2
        lw $t3, integer2     # carregando o conteúdo de integer2 para $t3
        add $s1, $t2, $t3    # guardando a soma dos conteúdos de $t2 e $t3 em $s1
        
        # Adicionando um inteiro qualquer e um inteiro da memória:
        lw $t4, integer1     # carregando o conteúdo de integer1 para $t4
        addi $s2, $t4, 75    # guardando a soma do conteúdo de $t4 e 75 em $s2

        li $v0, 10           # carregando código para finalizar o programa
        syscall              # finalizando o programa
