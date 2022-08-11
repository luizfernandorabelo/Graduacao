function alertChoices(colorArray, orderArray, totalChoices) {
  for (let i = 1; i <= totalChoices; i++)
    alert(i + 'ª escolha = ' + colorArray[orderArray.indexOf(i)]);
}

const color = ['Blue', 'Green', 'Red', 'Orange', 'Violet', 'Indigo'];
const order = [2, 1, 4, 5, 6, 3];

alertChoices(color, order, color.length);
