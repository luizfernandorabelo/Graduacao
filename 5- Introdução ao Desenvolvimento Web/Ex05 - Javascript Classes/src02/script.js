'use strict';

let inputURL = prompt('Entre com a URL');

function isValidURL(regex, inputURL) {
  return regex.test(inputURL);
}

if (isValidURL(/usp.br$/, inputURL)) alert('URL válida!');
else alert('URL inválida!');
