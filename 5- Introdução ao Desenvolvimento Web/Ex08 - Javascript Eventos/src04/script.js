'use strict';

const outputDisplay = document.querySelector('#output-display');
const clearKey = document.querySelector('#clear-key');
const equalsKey = document.querySelector('#equals-key');
const operandKeys = document.querySelectorAll('.operand-key');
const operationKeys = document.querySelectorAll('.operation-key');

let currentInput = '';
let inputs = [];

function isInputExpressionValid() {
  let operands = 0,
    operations = 0;
  inputs.forEach((input) => {
    if (isNaN(parseInt(input))) {
      operations++;
    } else {
      operands++;
    }
  });
  return !isNaN(parseInt(inputs[0])) && operands === operations + 1;
}

function evaluateExpression() {
  inputs = inputs.map((input) =>
    isNaN(parseFloat(input)) ? input : parseFloat(input)
  );
  evaluatePows();
  evaluateMultiplicationsAndDivisions();
  evaluateSumsAndSubtractions();
}

function evaluatePows() {
  for (let i = 1; i < inputs.length; i += 2) {
    if (inputs[i] === '^') {
      inputs[i + 1] = inputs[i - 1] ** inputs[i + 1];
      inputs[i - 1] = 1;
      inputs[i] = '*';
    }
  }
}

function evaluateMultiplicationsAndDivisions() {
  for (let i = 1; i < inputs.length; i += 2) {
    if (inputs[i] === '*') {
      inputs[i + 1] = inputs[i - 1] * inputs[i + 1];
      inputs[i - 1] = 0;
      inputs[i] = '+';
    } else if (inputs[i] === '/') {
      inputs[i + 1] = inputs[i - 1] / inputs[i + 1];
      inputs[i - 1] = 0;
      inputs[i] = '+';
    }
  }
}

function evaluateSumsAndSubtractions() {
  for (let i = 1; i < inputs.length; i += 2) {
    if (inputs[i] === '-') {
      console.log(
        'sub ',
        inputs[i - 1],
        inputs[i + 1],
        ', = ',
        inputs[i - 1] - inputs[i + 1]
      );
    } else {
      inputs[i + 1] = inputs[i - 1] + inputs[i + 1];
    }
  }
  inputs = [inputs[inputs.length - 1]];
}

operandKeys.forEach((operandKey) => {
  operandKey.addEventListener('click', () => {
    const operandText = operandKey.firstElementChild.innerText;
    currentInput += operandText;
    outputDisplay.firstElementChild.innerText += operandText;
  });
});

operationKeys.forEach((operationKey) => {
  operationKey.addEventListener('click', () => {
    const operationText = operationKey.firstElementChild.innerText;
    if (operationText === '-') {
      if (currentInput !== '') {
        inputs.push(currentInput);
        inputs.push('+');
      }
      currentInput = '-';
    } else {
      if (currentInput !== '') inputs.push(currentInput);
      inputs.push(operationText);
      currentInput = '';
    }
    outputDisplay.firstElementChild.innerText += operationText;
  });
});

clearKey.addEventListener('click', () => {
  currentInput = '';
  inputs = [];
  outputDisplay.firstElementChild.innerText = '';
});

equalsKey.addEventListener('click', () => {
  if (currentInput !== '') inputs.push(currentInput);
  if (inputs[0] === '+' || inputs[0] === '-') inputs.unshift('0');
  if (isInputExpressionValid()) {
    evaluateExpression();
    currentInput = inputs[0];
    inputs = [];
    outputDisplay.firstElementChild.innerText = currentInput;
  } else {
    alert('ERROR: Invalid Expression!');
  }
});
