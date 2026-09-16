# Module 1: Images, Memory, and the Vision Pipeline

**Estimated effort:** 10–12 hours across five sessions.

## Prerequisites

Complete [Module 0](../00_setup_environment/index.md). You need basic C++
syntax; this module introduces OpenCV and image-memory concepts from first
principles.

## Outcomes

By the end, you will be able to:

- Explain pixels, channels, depth, stride, and contiguous memory.
- Distinguish RGB, BGR, grayscale, and planar/interleaved layouts.
- Move safely between a custom image buffer and `cv::Mat`.
- Build a reproducible command-line image-processing application.

## Session plan

### 1. [Pixels and image matrices](session-01-pixels.md) (2 hours)

Learn the image-matrix model with dependency-free C++ exercises, then connect
rows, columns, channels, and stride to `cv::Mat`.

### 2. [Image memory layout](session-02-memory-layout.md) (2–2.5 hours)

Learn contiguous memory, row stride, and interleaved BGR storage. Design a
bounded `ImageView` over `std::vector` or `std::span` and trace pixel indexing
on a small synthetic image.

### 3. [Manual grayscale conversion](session-03-grayscale.md) (2–2.5 hours)

Load an image with OpenCV, copy it into the custom buffer, compute BGR-to-
grayscale manually, and save the result as a PNG. Compare it with OpenCV's
reference conversion.

### 4. [Resize, compare, and diagnose](session-04-resize-compare.md) (2–2.5 hours)

Implement nearest-neighbor resize. Produce an absolute-difference image,
diagnose a deliberately broken stride or channel-layout implementation, and
time row-major traversal.

### 5. Image-inspection utility (2–2.5 hours)

Combine the earlier work into an `image_inspect <input-image> [output-directory]`
command-line utility. It reports resolution, type, channel order, stride,
minimum, maximum, mean, histogram, and possible clipping; generated images are
saved to the output directory.

## Guided labs

1. Load an image, manually grayscale it, and save the result.
2. Find and correct a stride/channel bug.
3. Compare manual and OpenCV output with an absolute-difference image.
4. Benchmark row-major image traversal patterns.

## Completion checklist

- The manual grayscale output differs from the OpenCV reference by no more than
  one intensity value per pixel.
- All demonstrations run from the command line and save outputs as files; no
  desktop display is required.
- AddressSanitizer and UndefinedBehaviorSanitizer report no errors once the
  implementation is added.

## Next action

Begin Session 1 after confirming that the Module 0 OpenCV check runs locally.
