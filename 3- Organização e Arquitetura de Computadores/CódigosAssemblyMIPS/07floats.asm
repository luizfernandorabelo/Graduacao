.data
    .align 0
        out_1: .asciiz "O valor aproximado de PI é "        # armazenando out_1 como string na memória
        out_2: .asciiz "\nDigite um outro número real: "    # armazenando out_2 como string na memória
        out_3: .asciiz "Você digitou o número: "            # armazenando out_3 como string na memória
        
    .align 2
        PI: .float 3.14159                                  # armazenando 3.14159 como float na memória
        ZEROf: .float 0.0                                   # armazenando 0.0 como float na memória
        
.text
    .globl main
    
    main:
        lwc1 $f31, ZEROf        # carregando o valor ZEROf da memória para o registrador $f31 (esse registrador terá papel similar ao $zero)

        li $v0, 4               # carregando código para imprimir string
        la $a0, out_1           # carregando &out_1 da memória para o registrador $a0
        syscall                 # imprimindo string
        
        li $v0, 2               # carregando código para imprimir float
        lwc1 $f12, PI           # carregando o valor de PI da memória para o registrador $f12
        syscall                 # imprimindo float
        
        li $v0, 4               # carregando código para imprimir string
        la $a0, out_2           # carregando &out_2 da memória para o registrador $a0
        syscall                 # imprimindo string
        
        li $v0, 6               # carregando código para ler float
        syscall                 # lendo float (o valor vai para o registrador $f0)
        
        li $v0, 4               # carregando código para imprimir string
        la $a0, out_3           # carregando &out_3 da memória para o registrador $a0
        syscall                 # imprimindo string
        
        li $v0, 2               # carregando código para imprimir float
        add.s $f12, $f0, $f31   # movendo $f0 para o registrador $f12 (*$f31 = 0)
        syscall                 # imprimindo float
        
        li $v0, 10              # carregando código para finalizar o programa
        syscall                 # finalizando o programa
