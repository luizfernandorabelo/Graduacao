function createBookLi(bookObject) {
  const newLi = document.createElement('li');
  newLi.innerHTML = `Author: ${bookObject.author}, title: ${bookObject.title}, readingStatus: ${bookObject.readingStatus}`;
  return newLi;
}

let libraryObjectArray = [
  {
    author: 'Bill Gates',
    title: 'The Road Ahead',
    readingStatus: true,
  },
  {
    author: 'Steve Jobs',
    title: 'Walter Isaacson',
    readingStatus: true,
  },
  {
    author: 'Suzanne Collins',
    title: 'Mockingjay: The Final Book of The Hunger Games',
    readingStatus: false,
  },
];

libraryObjectArray.push({
  author: 'J.K. Rowling',
  title: 'Harry Potter',
  readingStatus: false,
});

const anotherBookObject = {};
anotherBookObject.author = prompt('Digite o autor do livro');
anotherBookObject.title = prompt('Digite o título do livro');
anotherBookObject.readingStatus =
  prompt('Digite o reading status (t ou f)').toLowerCase() === 't';

libraryObjectArray.push(anotherBookObject);

const allBooksUl = document.getElementById('all-books-ul');
const readingFalseBooksUl = document.getElementById('reading-false-books-ul');

for (let bookObject of libraryObjectArray) {
  allBooksUl.appendChild(createBookLi(bookObject));
  if (bookObject.readingStatus === false)
    readingFalseBooksUl.appendChild(createBookLi(bookObject));
}
