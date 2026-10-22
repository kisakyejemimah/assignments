# Credit Card Number Validation Explanation
-------------------------------------------------------------------------------------------------------------------
## 1. What the program does

It reads in a credit card number, then reports whether that number is
**valid** or **invalid**, using a real checksum algorithm (the **Luhn
algorithm**, a.k.a. the **Mod 10 check**) that credit card companies
actually use to catch typos and scanner misreads. It does *not* check
whether the card is real, active, or has funds — only whether the
*number itself* is internally consistent.

A number is only reported valid if **all three** of these hold:
1. It has **13–16 digits**.
2. It **starts with** a recognised issuer prefix: `4` (Visa), `5`
   (MasterCard), `37` (American Express), or `6` (Discover).
3. It **passes the Luhn checksum** (details in Section 3).

------------------------------------------

## 2. OOP concepts used.

| Concept | Where it shows up |
|---|---|
| **Abstraction** | `isValid()` hides *how* the Luhn check works behind one simple call — the caller doesn't need to know about digit-doubling or prefixes. |
| **Modularity / separation of concerns** | Each function does exactly one job (`getDigit` only collapses a two-digit number; `getSize` only counts digits). This mirrors OOP's idea that each unit of code should have a single responsibility. |
| **Function composition / reuse** | `isValid()` is built entirely out of the other six functions — it doesn't duplicate their logic. `prefixMatched()` reuses `getSize()` and `getPrefix()` rather than re-counting digits itself. |
| **Encapsulation (partial)** | The *details* of digit-manipulation are hidden inside small helper functions; `main()` never touches individual digits directly. |


```cpp
class CreditCard {
private:
    long long number; // encapsulated data — hidden from outside code

public:
    CreditCard(long long num) : number(num) {}
    bool isValid();                 // public interface

private:
    int  sumOfDoubleEvenPlace();    // implementation details —
    int  getDigit(int n);           // hidden from the outside
    int  sumOfOddPlace();           // (information hiding)
    bool prefixMatched(int d);
    int  getSize(long long d);
    long long getPrefix(int k);
};
```

Here, `number` becomes a **private data member** instead of a
parameter passed around everywhere; that's textbook **encapsulation**
(bundling data with the functions that operate on it) and
**information hiding** : the six helper functions are `private`
because outside code has no business calling them directly; only
`isValid()` is `public`.

--------------------------------------

## 3. The algorithm, step by step

Worked example: `4388576018402626`

**Step 1: Double every 2nd digit, counting from the right.**
Number the digits from the right: position 1, 2, 3, 4, ... Double
every digit sitting in an **even** position (2, 4, 6, ...). If
doubling produces a two-digit number (e.g. 6 × 2 = 12), add its two
digits together (1 + 2 = 3).

**Step 2: Add up all those (collapsed) doubled digits.**

**Step 3: Add up all the digits sitting in odd positions** (1, 3, 5,
...) exactly as they are; no doubling.

**Step 4: Add the Step 2 total and the Step 3 total together.**

**Step 5: Check divisibility by 10.** If the Step 4 total is exactly
divisible by 10, the number is valid. Otherwise it's invalid.

For `4388576018402626` this total is **not** divisible by 10 → invalid
(as given in the assignment). For `4388576018410707`, the same process
produces a multiple of 10 → valid.

### How each function maps onto these steps

| Function | Role |
|---|---|
| `getDigit(int number)` | Collapses a two-digit doubled value into one digit (part of Step 1) |
| `sumOfDoubleEvenPlace(long long number)` | Performs Steps 1–2 entirely: walks the number right to left, doubles even-position digits, collapses them, and totals them |
| `sumOfOddPlace(long long number)` | Performs Step 3: totals the odd-position digits |
| `isValid(long long number)` | Performs Step 4–5, plus the two extra business rules (digit count, valid prefix) |
| `getSize(long long d)` | Counts how many digits are in a number — used to check the 13–16 digit rule, and to know how many digits to compare when prefix-matching |
| `getPrefix(long long number, int k)` | Extracts the first `k` digits of `number`, so we can compare them against a known prefix |
| `prefixMatched(long long number, int d)` | Combines `getSize` and `getPrefix` to check whether `number` begins with the digits of `d` (e.g. does it start with `37`?) |

--------------------------------

## 4. Common mistakes / error points to watch for

- **Overflowing `int`.** A 16-digit number is far too big for a normal
  `int` (max ~2.1 billion, only 10 digits). Every function here uses
  `long long` for the card number itself — if you accidentally change
  any of those to `int`, the number silently corrupts (undefined
  behaviour / wraps around).
- **Doubling the wrong digits.** It's easy to get "odd vs even
  position, counting from the right" backwards and double the wrong
  set of digits. Trace through a short example by hand before trusting
  the code.
- **Forgetting to collapse two-digit doubles.** If you double a digit
  like `9` → `18` and forget to run it through `getDigit()`, you add
  `18` instead of `1 + 8 = 9` — the checksum will be wrong for any
  number containing digits 5–9 in a doubling position.
- **Off-by-one in `getPrefix`.** If you divide by the wrong power of
  10, you either get one digit too many or too few, and `prefixMatched`
  will always return false even for genuinely valid Visa/Amex numbers.
- **`getSize(0)` edge case.** A naive loop (`while (d > 0) { size++;
  d /= 10; })` returns `0` for the number `0`, when really `0` has one
  digit. Left unhandled, this can cause a divide-by-zero or an
  incorrect prefix comparison elsewhere.
- **Reading input as the wrong type.** If `cin >> cardNumber` reads
  into an `int` or a `string` instead of a `long long`, either the
  number truncates/overflows, or none of the arithmetic functions
  (which expect a number, not text) will compile or work correctly.
- **Leading zero cards.** Because the number is stored as `long long`,
  a card number that starts with a `0` would lose that leading zero
  (numerically, `0388...` is just `388...`). This is a known limitation
  of representing card numbers as integers rather than strings. 
- **Calling a function before it's declared.** Since `main()` is
  placed first in this file, function prototypes are declared at the
  top; delete them and the code won't compile, because C++ reads
  top-to-bottom and needs to know a function exists before it's used.
- **Testing with only one example.** Always test both a known-valid
  and a known-invalid number, a bug that only breaks the invalid path or vice versa is easier to miss with only one example.
---------------------------------------------------------------------------------------------------------------------
