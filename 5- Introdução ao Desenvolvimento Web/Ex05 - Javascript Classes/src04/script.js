'use strict';

class CircularBuffer {
  #free;
  #size;
  #elements;
  #currentPos;
  #oldestPos;

  constructor(size) {
    this.#free = size;
    this.#size = size;
    this.#elements = [];
    this.#currentPos = 0;
    this.#oldestPos = 0;
    for (let i = 0; i < size; i++) {
      this.#elements.push({ value: '', next: i + 1 });
    }
    this.#elements[size - 1].next = 0;
  }

  put(x) {
    if (this.#free === 0) this.pop();
    this.#elements[this.#currentPos].value = x;
    this.#currentPos = this.#elements[this.#currentPos].next;
    this.#free--;
  }

  pop() {
    if (this.#free === this.#size) throw new Error('Circular buffer is empty');
    let poped = this.#elements[this.#oldestPos].value;
    this.#elements[this.#oldestPos].value = '';
    this.#oldestPos = this.#elements[this.#oldestPos].next;
    this.#free++;
    return poped;
  }

  toString() {
    let string = 'Buffer = ';
    let element = this.#elements[this.#oldestPos];
    for (let i = 0; i < this.#size; i++) {
      if (element.value === '') break;
      string += `[${element.value}]${
        i !== this.#size - 1 && this.#elements[element.next].value !== ''
          ? ', '
          : ''
      }`;
      element = this.#elements[element.next];
    }
    return string;
  }

  get size() {
    return this.#size;
  }

  get free() {
    return this.#free;
  }
}

const buffer = new CircularBuffer(5);

console.log(buffer.size); // 5

try {
  buffer.size = 9;
} catch (e) {
  console.log(e.message);
}

buffer.put(8);
buffer.put('a');
buffer.put(3);
console.log(buffer.toString()); // Buffer = [8], ['a'], [3]

console.log(buffer.pop() + ' free: ' + buffer.free); // 8 free: 3

console.log(buffer.toString()); // Buffer = ['a'], [3]
buffer.put(4);
buffer.put(5);
buffer.put(6);
buffer.put(7);
console.log(buffer.toString()); // Buffer = [3], [4], [5], [6], [7]
buffer.pop();
buffer.pop();
buffer.pop();
buffer.pop();
buffer.pop();

try {
  buffer.pop(); // Error: Circular buffer is empty.
} catch (e) {
  console.log(e.message);
}
