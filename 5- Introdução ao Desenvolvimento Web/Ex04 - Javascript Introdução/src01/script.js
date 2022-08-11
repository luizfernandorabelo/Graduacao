function countLetters(name) {
  let totalLetters = 0;

  for (let character of name) {
    if (character.toLowerCase() != character.toUpperCase()) totalLetters++;
  }

  return totalLetters;
}

alert('Contador de Letras!');

let name = prompt('Digite o seu nome: ');

if (
  confirm(
    'Seu nome tem ' +
      countLetters(name) +
      ' letras, correto? (clique OK para confirmar)'
  )
)
  alert('👍');
else alert('Você está errado, conte novamente');
