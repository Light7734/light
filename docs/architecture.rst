Architecture
=========================
**Light** is a **modular** and feature rich engine with emphasis on the **entity component system** architectural design.
It is composed of numerous **modules** and prefers **composition over inheritance**.

Building Blocks
------------------------
Modules are the **building blocks** of Light.
Each module can provide one, and only one of the following:

- Library
    These modules provide some form of functionality. 
    They may depend on library modules.

    For instance, they may provide: asset parsing, logging, string functions,
    math functions, containers, etc.

    Library modules may also **wrap** a third-party library and provide an interface following Light's coding guidelines.

    This way:

    * Unsafe libraries, often native C libraries, can be made safer (without sacrificing performance).
    * Coding conventions can be consistent across all lines of code in other modules.
    * Deprecated and confusing conventions (eg. out parameters) can be wrapped away and replaced by simpler interfaces.
    * It may be possible to provide only the required symbols from a library.

- Tool
    These modules compile as executables that provide tooling.
    They may depend on any other module type.

    An example of a **tool** module is the "AssetBaker" that relieves other modules
    from linking to large third-party asset readers (and optimizers) and bakes assets' content 
    in a common, and often optimized, format.

- Component
    These modules specify POD structures to be used as components of one or more systems.
    They shall not depend on any other module. This separation (of components and system modules) is for 2 reasons: 

    First, for simple re-usability of **components** between multiple **systems** as it is quite likely
    for more than 1 **system** to depend on a component.
    For instance, **physics simulation** and **rendering** both depend on the **TransformationComponent**

    Second, even if a component is used solely by **1 system**, decoupling the **component** from the
    **system's implementation** allows us to provide alternative implementations for
    a system. For instance, we can have a **polygon-renderer** and a **raytracer** for our
    rendering system.

- System
    System modules may depend on any number of modules but must depend on at least one component module.

    These modules implement an aspect of the engine, e.g. physics system, rendering system, 
    audio system, networking system, script system, etc. 
    They implement a common **system interface** and may periodically **tick** to execute their logic
    and **mutate** different components while doing so.

- Main
    **Light** is the stock implementation of the **main** module. It's basically our engine.
    You may design and use an alternative implementation.

    The main module acts as the **aggregator** and **synchronizer** of a required module list.
    It synchronizes between multiple modules using a concept called **tick dependencies**.

    Since we want to maximally utilize our hardware, we need to have as much concurrency as possible.
    One obvious way to increase concurrency is to make multiple systems tick (execute their logic) 
    in parallel.

    But we can't just tick haphazardly, we need proper **synchronization**.
    Let's break down how synchronization works with **tick dependencies** by briefly going
    through different module types:

    **Tool** modules are executables (eg. AssetBaker). They don't need any external synchronization.

    **Library** modules simply provide reusable functionality for **tool** and **system** modules.

    **Component** modules, even more simply, provide a set of POD structures.

    **System** modules, however, bring about a bit of complexity.
    They need to execute a piece of code periodically, which may cause **mutations**.

    For instance, a **physics simulation system** needs to tick every frame (or multiple times 
    a frame at fixed intervals) to simulate physics, this simulation may **mutate** one
    or more components, such as the **TransformationComponents**.

    Meanwhile, the **rendering system** might use the **TransformationComponent** for vertex shader operations
    to determine where things should end up on the screen. 
    We can't be **mutating** a component in one thread while **reading** it in another, this causes all sorts
    of nasty problems. Hence why we need synchronization.

    Systems can think of synchronization of their logic to be done in one of 3 ways: 
    **external**, **internal**, and **unsynchronized**.

    - **Unsynchronized**: 
        As evident from the name, no syncing needs to be done for these parts of a system.

    - **Internal**: 
        This type of synchronization is handled internally by the module and does
        not concern other systems.

    - **External**: 
        This is the synchronization done by the main module (Light). And can be achieved
        by specifying a list of tick dependencies.

    The system interface provides 3 tick functions: 

    - **tick_pre_unsync**:
        This gets called for all **active systems** at the same time before the frame starts.
        Light waits for the execution of all **tick_pre_unsync** functions to finish before proceeding to **tick_sync**.
        This is usually for systems to handle internally synchronized pre-frame logic.

    - **tick_sync**: 
        This relies on the tick dependencies of a system. 
        A tick dependency simply marks a **type of component** as a **mutable** or **immutable** dependency for
        a particular **system**. If system **A** shares only **immutable** dependencies with system **B**, or
        if system **A** shares no dependencies with system **B**, they can tick together.

        If system **A** has a **mutable** dependency with a component, then all systems that have either
        **mutable** or **immutable** dependency with that component need to tick before or after system **A's**
        tick.

    - **tick_post_unsync**: 
        Same as **tick_pre_unsync**, but happens after all **tick_sync** calls
        have been executed.

    You might be wondering why we're bothering with specifying tick dependencies between
    such high-level concepts as **systems** where we could manually do the external synchronization
    between them.

    There may be truth in that claim, but our intention here is to free **Light** from knowing
    about the implementation details of our systems and instead make it simply provide a framework for setting up 
    and running multiple systems together.

    Furthermore, now our **systems** don't need to know anything about the existence of other systems either
    and their logic is completely isolated.
    
Performance
----------------
**Light** engine aims to keep a high-performant design on all levels of the engine, from the grand architecture to the low-level implementations.
It also tries to ensure a consistent performance across platforms and APIs. 
We achieve this by not thinking of performance as a concern for later times and put it as one
of our first priorities.

Some of the main techniques **Light** utilizes to ensure optimal code performance:

- Hardware Friendly Architecture

- Native Support
    Light provides native support for the supported platforms and architectures.
    It also provides native graphics API support for all the supported operating systems:
    Metal for MacOS, DirectX12 for Windows and Vulkan for the rest.

- Baking
    Light bakes and optimizes anything that can be baked as soon as it can.

    For assets, this will significantly decrease our load times because optimized (and specialized) data can be directly
    streamed to RAM/VRAM without intermediate processing.

    We don't only bake assets like models, images and audio. We also bake anything about the scene
    that's bake-able in any sense.

- Low Memory Footprint
    Memory is sacred! That's my personal philosophy. I always use low memory-footprint applications.
    I value and respect memory. I worship memory. I pray to the memory gods, so that I may never run
    out of memory.
    
    Games and simulations naturally have high memory consumption. But that fact should not give us
    a free pass for ignoring our memory footprint. Light engine respects its user's hardware by
    not being wasteful and always optimizing its memory consumption (alongside its performance).

    Every byte matters!

- Minimal Indirection
    Light minimizes unnecessary indirections and makes friends with the compilers by
    providing them as much context as possible. It uses compile-time paradigms and principles before
    considering (necessary) indirections.

    All problems in programming can be solved by another level of indirection. But perhaps not performance
    problems.

- Rigorous Testing

State
----------------
The data in Light engine can be coarsely divided into 4 types:

- Shared
    Components are the only way for our systems to have data shared between themselves.
    They are laid out in the most reasonably efficient way possible by our ECS implementation.
    Currently we use **EnTT**, however we **may** roll our own implementation in the future if needs be.

- Internal
    Systems can hold any amount of internal state as they wish. Light however won't go over-board
    and respects the hardware's cache locality when it's iterating over a set of components.

- Transient
    Mostly just the stack. 

- Cold
  Cold state is everything that lives on the disk, saved game-state, baked assets, etc.
