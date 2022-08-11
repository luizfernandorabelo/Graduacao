'use strict';

function breakOriginalPLinesToDifferentParagraphs(
  originalParagraphContent,
  lastBodyChild
) {
  let wordArray, delimiterArray;
  ({ wordArray, delimiterArray } = buildWordAndDelimiterArrays(
    originalParagraphContent
  ));

  let paragraphContent = '';

  for (let i = 0; i < delimiterArray.length; i++) {
    paragraphContent += wordArray[i] + delimiterArray[i];
    if (delimiterArray[i] !== ' ') {
      document.body.insertBefore(
        createParagraph(paragraphContent),
        lastBodyChild
      );
      paragraphContent = '';
    }
  }
}

function buildWordAndDelimiterArrays(originalContent) {
  const wordArray = [],
    delimiterArray = [];

  const splittedContent = originalContent.split(' ');

  for (let string of splittedContent) {
    if (isStringLineDelimiter(string)) {
      wordArray.push(string.substring(0, string.length - 1));
      delimiterArray.push(string[string.length - 1]);
    } else {
      wordArray.push(string);
      delimiterArray.push(' ');
    }
  }

  return { wordArray, delimiterArray };
}

function isStringLineDelimiter(string) {
  return (
    string.endsWith('.') ||
    string.endsWith('!') ||
    string.endsWith('?') ||
    string.endsWith(':')
  );
}

function createParagraph(content) {
  const newParagraph = document.createElement('p');
  newParagraph.innerHTML = content;
  return newParagraph;
}

function updateH1Color(h1) {
  const originalH1Content = h1.innerHTML;
  const wordArray = originalH1Content.split(' ');

  addColorClassToWordArray(wordArray);

  h1.innerHTML = wordArray.join(' ');
}

function updatePColors(paragraphs) {
  paragraphs.forEach((p) => updatePcolor(p));
}

function updatePcolor(paragraph) {
  const paragraphWords = paragraph.innerHTML.split(' ');

  addColorClassToWordArray(paragraphWords);

  paragraph.innerHTML = paragraphWords.join(' ');
}

function addColorClassToWordArray(wordArray) {
  for (let i = 0; i < wordArray.length; i++) {
    const currentWord = wordArray[i];
    let startIdx, endIdx;
    ({ startIdx, endIdx } = getWordStartAndEndIdxs(currentWord));
    wordArray[i] = applyColor(currentWord, startIdx, endIdx);
  }
}

function getWordStartAndEndIdxs(word) {
  let startIdx = 0;
  let endIdx = word.length - 1;

  while (
    startIdx < word.length &&
    word[startIdx].toUpperCase() === word[startIdx].toLowerCase()
  )
    startIdx++;

  while (
    endIdx >= 0 &&
    word[endIdx].toUpperCase() === word[endIdx].toLowerCase()
  )
    endIdx--;

  return { startIdx, endIdx };
}

function applyColor(word, startIdx, endIdx) {
  const wordLength = endIdx - startIdx + 1;

  if (wordLength === 4 || wordLength === 5)
    return (
      word.substring(0, startIdx) +
      `<span class="blue">${word.substring(startIdx, endIdx + 1)}</span>` +
      word.substring(endIdx + 1, word.length)
    );
  else if (wordLength === 6)
    return (
      word.substring(0, startIdx) +
      `<span class="purple">${word.substring(startIdx, endIdx + 1)}</span>` +
      word.substring(endIdx + 1, word.length)
    );
  else if (wordLength >= 8)
    return (
      word.substring(0, startIdx) +
      `<span class="pink">${word.substring(startIdx, endIdx + 1)}</span>` +
      word.substring(endIdx + 1, word.length)
    );

  return word;
}

const originalParagraph = document.querySelector('p');
const h1 = document.querySelector('h1');
const button = document.querySelector('button');

breakOriginalPLinesToDifferentParagraphs(originalParagraph.innerHTML, button);
originalParagraph.remove();

button.addEventListener('click', buttonClickedCallback);

function buttonClickedCallback() {
  updateH1Color(h1);
  updatePColors(document.querySelectorAll('p'));
  button.removeEventListener('click', buttonClickedCallback);
}
