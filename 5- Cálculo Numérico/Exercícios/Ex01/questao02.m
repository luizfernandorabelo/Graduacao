% Um erro aceitável pode ser definido no
% sentido de que, se a diferença em módulo
% de quaisquer dois valores for menor que
% o erro, os dois valores são considerados
% iguais. Quanto menor o erro, mais preciso
% será o resultado.

ERRO_ACEITAVEL = 1e-15;

x = 0;

for i = 1:30
    x = x + 1/5;
    if abs(x - 3.6) <= ERRO_ACEITAVEL
        disp(x);
    end
end
