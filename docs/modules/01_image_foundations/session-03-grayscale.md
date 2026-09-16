# Session 3: Manual Grayscale Conversion

**Time:** about 2–2.5 hours  
**Prerequisite:** complete [Session 2](session-02-memory-layout.md).

This session converts fixed BGR pixels to grayscale with ordinary C++20 first.
The final connection shows how to compare the same result with OpenCV on real
images.

---

## Goals

By the end of this session, you can:

- Explain why grayscale is a weighted combination of color channels.
- Convert one BGR pixel to an 8-bit grayscale value manually.
- Convert a small interleaved BGR row using the layout from Session 2.
- Measure the largest difference between manual and reference outputs.

---

## Core idea: brightness is not an equal channel average

Human vision is more sensitive to green than red, and more sensitive to red
than blue. A useful grayscale approximation therefore gives green the largest
weight:

```text
gray = 0.299 × red + 0.587 × green + 0.114 × blue
```

To avoid floating-point arithmetic, the exercises use weights that add up to
`256`:

```text
gray = (77 × red + 150 × green + 29 × blue + 128) / 256
```

The `+128` rounds the integer division to the nearest value. Because the input
is **BGR** storage, code receives `blue`, `green`, then `red`, but applies each
weight to the color's meaning—not its memory position.

For a pure red BGR pixel `(0, 0, 255)`:

```text
gray = (77 × 255 + 150 × 0 + 29 × 0 + 128) / 256
     = 77
```

---

## Build commands

Each file below is complete and needs only the C++20 standard library. From the
repository root, compile one with:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic \
  modules/01_image_foundations/session_03/exercises/01_grayscale_pixel.cpp \
  -o /tmp/01_grayscale_pixel
/tmp/01_grayscale_pixel
```

Starter programs compile but intentionally fail an `assert` until you replace
their `TODO`. Solution programs compile and run successfully with the same
command after replacing `exercises` with `solutions`.

The unfinished grayscale functions contain lines such as
`static_cast<void>(blue);`. They do not change `blue` or calculate anything.
They explicitly mark a parameter as intentionally unused while its `TODO` is
unfinished, keeping the `-Wextra` compiler check quiet. Once your formula uses
the parameter, remove that line; the solution files do not need it.

---

## Exercise 1: Convert one BGR pixel

Implement the integer grayscale formula. Pure red BGR `(0, 0, 255)` must
produce `77`.

```cpp
--8<-- "modules/01_image_foundations/session_03/exercises/01_grayscale_pixel.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_03/solutions/01_grayscale_pixel.cpp"
```

</details>

---

## Exercise 2: Convert an interleaved BGR row

The first pixel is pure red and the second is white. Complete the same
conversion function, then trace how `pixel * channels` selects each BGR triplet.

```cpp
--8<-- "modules/01_image_foundations/session_03/exercises/02_bgr_row_to_gray.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_03/solutions/02_bgr_row_to_gray.cpp"
```

</details>

---

## Exercise 3: Check a reference difference

Manual integer arithmetic may differ from a library reference by a small
rounding amount. Find the largest absolute difference between two grayscale
outputs. The example must report `1`.

```cpp
--8<-- "modules/01_image_foundations/session_03/exercises/03_max_difference.cpp"
```

<details>
<summary>Show solution</summary>

```cpp
--8<-- "modules/01_image_foundations/session_03/solutions/03_max_difference.cpp"
```

</details>

---

## OpenCV connection

OpenCV stores normal color images in BGR order. On a real image, use its
reference conversion and compare it with your manual result:

```cpp
cv::Mat bgr = cv::imread("input.png", cv::IMREAD_COLOR);
cv::Mat reference_gray;
cv::cvtColor(bgr, reference_gray, cv::COLOR_BGR2GRAY);
```

Later in Module 1, the manual conversion will write one grayscale value per
pixel and compare the manual image with `reference_gray` using `cv::absdiff`.
The acceptance target is a maximum difference of at most `1` intensity level
per pixel.

---

## C++ casts: making a conversion explicit

A **cast** asks C++ to view or convert a value as another type. Prefer an
explicit named cast when a conversion needs explanation; it makes the intent
visible during review.

| Cast | What it does | Use it when | Rule of thumb |
| --- | --- | --- | --- |
| `static_cast<T>(value)` | Performs a checked-at-compile-time conversion such as `double` to `int`, or a known base/derived conversion. | The conversion is intentional and the types are related by a normal C++ rule. | The usual cast for numeric image calculations. |
| `dynamic_cast<T>(pointer)` | Checks a polymorphic inheritance conversion at runtime. A failed pointer cast becomes `nullptr`. | Working with class hierarchies that have virtual functions. | Not needed for pixel buffers or `cv::Mat` basics. |
| `const_cast<T>(value)` | Adds or removes `const` or `volatile` qualification. | Almost never in new code; only when an API incorrectly requires a mutable view of an object that was originally mutable. | Never write through it if the original object was actually `const`; that is undefined behavior. |
| `reinterpret_cast<T>(value)` | Reinterprets bits, addresses, or unrelated pointer types. | Rare low-level platform code with explicit alignment, lifetime, and aliasing guarantees. | Avoid it in course image code; use normal indexing or copying instead. |

This session uses `static_cast<void>(blue)` in unfinished starter code:

```cpp
static_cast<void>(blue);
```

It converts `blue` to `void`, which discards the value. The line has no runtime
effect; it simply states, “this parameter is intentionally unused for now,” so
the compiler does not report a warning before the TODO is completed.

For a real numeric conversion, the same cast makes possible precision loss
visible:

```cpp
const double brightness = 77.8;
const int gray = static_cast<int>(brightness);  // gray is 77: fractional part is removed.
```

Avoid C-style casts such as `(int)brightness`. They can silently perform more
than one kind of conversion, making unsafe behavior harder to notice.

---

## Review quiz

<form class="quiz" data-answer="b" data-explanation="Green receives the largest weight because human brightness perception is strongest for green light.">
  <fieldset>
    <legend>1. Which channel receives the largest grayscale weight?</legend>
    <label><input type="radio" name="session3-q1" value="a"> Blue</label><br>
    <label><input type="radio" name="session3-q1" value="b"> Green</label><br>
    <label><input type="radio" name="session3-q1" value="c"> Red</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="The input is BGR, so blue is first and red is third, but the luminance weights still apply to their color meanings.">
  <fieldset>
    <legend>2. Which arguments describe a pure red BGR pixel?</legend>
    <label><input type="radio" name="session3-q2" value="a"> (255, 0, 0)</label><br>
    <label><input type="radio" name="session3-q2" value="b"> (0, 255, 0)</label><br>
    <label><input type="radio" name="session3-q2" value="c"> (0, 0, 255)</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="a" data-explanation="For pure red, only 77 × 255 contributes, so the rounded division produces 77.">
  <fieldset>
    <legend>3. What grayscale value does the exercise expect for pure red?</legend>
    <label><input type="radio" name="session3-q3" value="a"> 77</label><br>
    <label><input type="radio" name="session3-q3" value="b"> 150</label><br>
    <label><input type="radio" name="session3-q3" value="c"> 255</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="b" data-explanation="The largest absolute difference catches the worst pixel disagreement between two equally sized outputs.">
  <fieldset>
    <legend>4. Why measure the maximum absolute difference?</legend>
    <label><input type="radio" name="session3-q4" value="a"> To count image channels.</label><br>
    <label><input type="radio" name="session3-q4" value="b"> To find the worst pixel disagreement.</label><br>
    <label><input type="radio" name="session3-q4" value="c"> To make the image brighter.</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

<form class="quiz" data-answer="c" data-explanation="cv::cvtColor with COLOR_BGR2GRAY is OpenCV's BGR-to-grayscale reference conversion.">
  <fieldset>
    <legend>5. Which OpenCV call creates the grayscale reference image?</legend>
    <label><input type="radio" name="session3-q5" value="a"> cv::imread</label><br>
    <label><input type="radio" name="session3-q5" value="b"> cv::absdiff</label><br>
    <label><input type="radio" name="session3-q5" value="c"> cv::cvtColor</label>
  </fieldset>
  <button type="button" class="quiz-check">Check answer</button>
  <p class="quiz-result" aria-live="polite"></p>
</form>

---

## Completion check

- Explain why the green weight is larger than the blue weight.
- Compute the grayscale value for one BGR pixel by hand.
- Compile and run all three solution files.
- Answer all five quiz questions correctly.

Next: return to the [Module 1 overview](index.md) before starting Session 4.

---

## C++ concepts used in this session

| C++ feature | Meaning here |
| --- | --- |
| Function parameters | `bgr_to_gray(int blue, int green, int red)` receives one pixel's channel values as named inputs. |
| `return` | Sends a computed grayscale or difference value back to the caller. |
| `const std::array<int, N>&` | A read-only reference parameter. It avoids copying the array while promising not to modify it. |
| `for` loop | Repeats work over each pixel or each output value. The loop index advances with `++index`. |
| Ternary operator `condition ? a : b` | Chooses between two expressions. The difference exercise uses it to make a non-negative value. |
| `std::max(a, b)` | Returns the larger value; the reference check keeps the largest difference seen so far. |
| Integer division | Dividing two `int` values drops the fractional part. Adding `128` before dividing by `256` performs nearest-integer rounding here. |
| `static_cast<void>(value)` | Explicitly converts a currently unused value to `void`. It has no runtime effect; the starter files use it only to avoid unused-parameter warnings before the TODO is completed. |
| `assert(condition)` | Makes the expected grayscale and maximum-difference results runnable checks. |
