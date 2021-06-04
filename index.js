
function tryCatchWarp(name, callback) {
    try {
        const result = callback();
        console.log(`=== ${name} ===`);
        return result;
    } catch (error) {
        console.log(`=== ${name} ===`);
        console.log(`FAILED`);
        console.error(error);
        console.log(`===============`);
    }
    return null;
}


function start() {
    const result = tryCatchWarp("Bind",() => require('bindings')('test.node'));
    if (!result) return;
    const keys = Object.keys(result);
    for (const key of keys) {
        const obj = result[key];
        if(typeof obj === 'function') {
            console.log(`[type function] ${key}()`)
        } else {
            console.log(`[type ${typeof obj}] ${key}: ${obj}`)
        } 
    }
    console.log('========================');
    const helloWorldString = tryCatchWarp('hello world', () => result.helloWorld());
    if (helloWorldString === null) return;
    console.log(helloWorldString);


    const shouldReturnSameString = tryCatchWarp('return string', () => result.writeString('Same string'));
    if (shouldReturnSameString === null) return;
    console.log(shouldReturnSameString);
  
    const ccppReverseString = tryCatchWarp('Reverses string', () => result.reverseString('Same string'));
    if (ccppReverseString === null) return;
    console.log(ccppReverseString);
}


start();


