'use strict';

const expressions = [
  'entered in the room upset, holding',
  "can't get rid of",
  'usually sleeps with',
  'accidentally sat on',
  'woke up his friend using',
];

const btn = document.querySelector('#lib-button');
const storyDiv = document.querySelector('#story');

function makeMadTalk() {
  const inputs = retrieveUserInputs();

  if (!areInputsValid(inputs)) {
    alert('Check the inputs and try again!');
    return;
  }

  const p = document.createElement('p');

  console.log(inputs);

  p.innerText =
    inputs.name +
    ' ' +
    expressions[parseInt(Math.random() * expressions.length)] +
    ' ' +
    `${inputs.gender === 'male' ? 'his' : 'her'}` +
    ' ' +
    inputs.adjective +
    ' ' +
    inputs.noun +
    '!';

  storyDiv.childNodes.forEach((child) => child.remove());

  storyDiv.appendChild(p);
}

function areInputsValid(inputs) {
  for (let input in inputs) {
    if (inputs[input] === '') return false;
  }
  return true;
}

function retrieveUserInputs() {
  return {
    noun: document.querySelector('#noun').value,
    adjective: document.querySelector('#adjective').value,
    name: document.querySelector('#name').value,
    gender: document.querySelector('input[name=gender]:checked').value,
  };
}

btn.addEventListener('click', makeMadTalk);
