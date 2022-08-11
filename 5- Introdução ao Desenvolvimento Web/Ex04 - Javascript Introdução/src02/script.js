let result = '';

for (let i = 0; i <= 15; i++) {
  result += i % 2 != 0 ? i + ' is odd<br>' : i + ' is even<br>';
}

document.getElementById('container').innerHTML = result;
