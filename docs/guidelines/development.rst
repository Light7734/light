.. guidelines/development

Development Strategy
===================================================================================================
Defines:

- A **unit of work**.
- A **pipeline** for making changes ---should **minimize ambiguity**.
- A way for **distributing work** and **tracking productivity**.

An **unpragmatic strategy** is utterly useless. It should pull our minds out from the **engineering dreamland**, and make us focus on the **product delivery**.

.. note::
   **Forgejo issues** is used as the project-management tool.
   No need for fancy boards or 3rd party apps. Simple tags, titles, milestones, etc... should suffice.

Cycle
---------------------------------------------------------------------------------------------------
A cycle is one **step** in development, 1 cycle == 1 issue, and it consists of 4 stages:

1 - Make it known
    - Write the commit title.
        - This limits the **scope of changes** and gives you a very specific **goal** to work towards.
        - The message should follow the project's **commit message specifications**.

    - Make an issue.
        - Git is a **version-control** tool, not a **project-management** tool.
        - Preferably, provide a very brief description ---This may be used in the commit message's body.

2 - Make it work
    - Write high-level tests that confirms the cycle's requirements are met.
        - That is, specify requirements in a programming language instead of English.
        - You're done when all the tests pass.
        - Preferably write the tests first, but it's okay to start with the interface.
        - Tests **may** not be necessary depending on the requirements and commit type.

    - **Make it work** doesn't mean liberally producing substandard code, you should:
        - Follow project's **conventions**.
        - Follow **best practices** and **proven swe principles**.
        - Enable **warnings as errors**.
        - Enable **static analysis**.
        - Don't break existing tests.
        - Have the overall picture in mind.

3 - Make it right
    - Test driven refactoring
        - Now you have a better picture of how things relate and work.
        - Switch to a TDD-style development to do the refactoring while following swe best-practices and proven-principles.

4 - Make it fast
    - This is an engine, at the end of the day, **performance** is king.
    - Get a performance and/or memory profile and try to alleviate the bottlenecks.
    - Avoid premature optimizations, be certain what you change has performance benefits.

Sprint
---------------------------------------------------------------------------------------------------
A sprint is the collection of all the finished cycles in **one week**.
They start from **Monday mornings**, and end on **Sunday nights**,
where we'll do a **12hr coding marathon** (streamed on Discord) to wrap everything up.

Sprints begin by **defining** what cycles/issues are expected to be done.
And end by **reflecting** on the results, which may **affect** our future approach.

Commit Message Specification
---------------------------------------------------------------------------------------------------
The project follows the `Conventional Commits Specification <https://www.conventionalcommits.org/en/v1.0.0-beta.4>`_.

.. code-block:: md

    <type>[optional scope]: <description>

    [optional body]

    [optional footer]

With the following commit types:

- feat
    - For adding a new feature.
    - Causes a **minor** bump in version.

- fix
    - For changes that fix one or more bug.
    - Causes a **patch** bump in version.

- refactor
    - For non feat/fix changes that improve the implementation and/or the interface.
    - Causes a **patch** bump in version.

- perf
    - For changes that (hopefully) improve the performance.
    - Causes a **patch** bump in version.

- build
    - For changes that affect the build system or external dependencies.
    - Causes a **patch** bump in version.

- asset
    - For changes to the files under the ``/data`` directory.
    - Causes a **patch** bump in version.

- test
    - For adding missing tests or correcting the existing tests.
    - Does not affect the version.

- chore
    - For releases, .gitignore changes, deleting unused files, etc.
    - Does not affect the version.

- ci
    - For changes to our CI configuration files and scripts, including files under ``/tools/ci``.
    - Does not affect the version.

- docs
    - For changes to the documentations.
    - Does not affect the version.

.. note::

    Since we're in beta, any commit might change the api, no need for ! (breaking) tags.

Semantic Versioning
---------------------------------------------------------------------------------------------------
Coupled with conventional commit style messages, we can automajically version the project following
the **Semantic Versioning 2.0.0** specifications.

The full version identifier consits of a version core (major.minor.patch) + label + hexsha of the commit.
Using the following format:


.. code-block:: md

    <major>.<minor>.<patch>-<label>+<short_hexsha>

    eg.
    0.8.1-kitten+ea898 
    0.5.0-kitten+01d85
    1.5.0-akasha+7de53

    kitten refers to all pre-release (1.0.0) versions


The shortened hexsha of a commit is obtained by:
``git rev-parse --short=5 <commit_hexsha>``
