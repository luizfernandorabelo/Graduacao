function getItemOccurrences(array, targetItem) {
  let occurrences = 0;

  for (let item of array) {
    if (item == targetItem) occurrences++;
  }

  return occurrences;
}

function getMostFrequentItemAndOccurrences(array) {
  if (array.length == 0) return { item: null, occurrences: 0 };

  let mostFrequentItem = array[0];
  let mostFrequentOccurrence = getItemOccurrences(array, array[0]);

  for (let i = 1; i < array.length; i++) {
    let itemOccurrence = getItemOccurrences(array, array[i]);
    if (itemOccurrence > mostFrequentOccurrence) {
      mostFrequentItem = array[i];
      mostFrequentOccurrence = itemOccurrence;
    }
  }

  return { item: mostFrequentItem, occurrences: mostFrequentOccurrence };
}

const array = [3, 'a', 'a', 'a', 2, 3, 'a', 3, 'a', 2, 4, 9];

const result = getMostFrequentItemAndOccurrences(array);

document.getElementById('container').innerHTML =
  result.item + ' (' + result.occurrences + ' times) <br>';
