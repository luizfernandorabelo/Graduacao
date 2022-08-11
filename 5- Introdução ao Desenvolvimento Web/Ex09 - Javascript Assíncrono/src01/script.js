const URL = 'https://reqres.in/api/unknown/';

const input = document.querySelector('#color-number');
const btn = document.querySelector('#change-color-btn');
const colorName = document.querySelector('#color-name');
const colorHex = document.querySelector('#color-hex');
const colorSample = document.querySelector('#color-sample');

async function logData() {
  const response = await fetch(URL + '4');
  const object = await response.json();

  console.log(object);
}

async function updateNewColor(colorNumber) {
  try {
    const response = await fetch(URL + colorNumber);
    const object = await response.json();
    colorName.innerText = object.data.name;
    colorHex.innerText = object.data.color;
    colorSample.style.backgroundColor = object.data.color;
  } catch (err) {
    console.log(err);
    alert('Color not found!');
  }
}

// A:
logData();

// B:
btn.addEventListener('click', () => {
  updateNewColor(input.value);
});
