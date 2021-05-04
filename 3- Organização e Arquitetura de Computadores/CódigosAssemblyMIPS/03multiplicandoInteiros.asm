.data
    .align 2
        integer1: .word 2    # armazenando o valor 2 (int32) na memória
        integer2: .word 5    # armazenando o valor 5 (int32) na memória

.text
    .globl main
    
    main:
        lw $t0, integer1     # carregando integer1 da memória para o registrador $t0
        lw $t1, integer2     # carregando integer2 da memória para o registrador $t1
        mul $s0, $t0, $t1    # guardando a multiplicação entre os conteúdos de $t0 e $t1 em $s0

        li $v0, 10           # carregando código para finalizar o programa
        syscall              # finalizando o programa
