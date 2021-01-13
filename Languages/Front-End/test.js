function* makeRangeIterator(start = 0, end = 100, step = 1) {
    let iterationCount = 0;
    for (let i = start; i < end; i += step) {
        iterationCount++;
        yield i;
    }
    return iterationCount;
}

let it = makeRangeIterator(0, 10, 1.5)
for (let result = it.next(); !result.done; result = it.next())
    console.log(result.value)