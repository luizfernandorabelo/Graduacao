const URL = 'https://reqres.in/api/unknown/';

const input = document.querySelector('#color-number');
const btn = document.querySelector('#change-color-btn');
const colorName = document.querySelector('#color-name');
const colorHex = document.querySelector('#color-hex');
const colorSample = document.querySelector('#color-sample');

function updateNewColor(colorNumber) {
  fetch(URL + colorNumber)
    .then((response) => response.json())
    .then((object) => {
      colorName.innerText = object.data.name;
      colorHex.innerText = object.data.color;
      colorSample.style.backgroundColor = object.data.color;
    })
    .catch((err) => {
      console.log(err);
      alert('Color not found!');
    });
}

btn.addEventListener('click', () => {
  updateNewColor(input.value);
});
