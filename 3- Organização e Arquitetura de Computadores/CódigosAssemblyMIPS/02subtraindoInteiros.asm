.data
    .align 2
        integer1: .word 25   # armazenando o valor 25 (int32) na memória
        integer2: .word 75   # armazenando o valor 75 (int32) na memória

.text
    .globl main
    
    main:
        # Subtraindo inteiros quaisquer:
        li $t0, 25           # carregando o valor 25 para o registrador $t0
        li $t1, 75           # carregando o valor 75 para o registrador $t1
        sub $s0, $t1, $t0    # guardando a subtração dos conteúdos de $t1 e $t0 em $s0
    
        # Subtraindo inteiros vindos da memória:
        lw $t2, integer1     # carregando o conteúdo de integer1 para $t2
        lw $t3, integer2     # carregando o conteúdo de integer2 para $t3
        sub $s1, $t3, $t2    # guardando a subtração de $t3 e $t2 em $s1
        
        # Subtraindo um inteiro qualquer e um inteiro da memória:
        lw $t4, integer2     # carregando o conteúdo de integer2 para $t4
        subi $s2, $t4, 25    # guardando a subtração de $t4 e 25 em $s2. IMPORTANTE: subi não é uma operação do assembly mips. IDEs aceitam esse comando mas ele é traduzido como 'addi $tx, ty, -const'

        li $v0, 10           # carregando código para finalizar o programa
        syscall              # finalizando o programa
