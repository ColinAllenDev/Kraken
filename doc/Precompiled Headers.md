# Precompiled Headers

---

Precompiled Headers are exactly as they sound. To improve performance in large projects we take predefined headerfiles and compile them once so the compiler doesn't have to parse through headers and translate them into machine code before compiling.   

**Tips**
- Do not put header files that change often in your PCH
- External libraries should often be in your PCH because you are unlikely to ever touch them (e.g. STL, Windows.h)
- A con of putting header files in a PCH is that it abstracts the specific includes you want to include in your other source/header files

In KrakenEngine our precompiled headers are stored in kepch.h