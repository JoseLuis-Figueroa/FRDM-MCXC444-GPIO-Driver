# Contributing to FRDM-MCXC444 GPIO Driver

Thank you for considering contributing to the **FRDM-MCXC444 GPIO Driver** project!  
We welcome all contributions, whether it's fixing bugs, improving documentation, or adding new features.

---

## Table of Contents

1. [Getting Started](#getting-started)  
2. [Code of Conduct](#code-of-conduct)  
3. [Ways to Contribute](#ways-to-contribute)  
4. [Development Setup](#development-setup)  
5. [Coding Standards](#coding-standards)  
6. [Making a Pull Request](#making-a-pull-request)  
7. [Commit Message Guidelines](#commit-message-guidelines)  
8. [Doxygen Documentation](#doxygen-documentation)  
9. [Need Help?](#need-help)  

---

## Getting Started

To contribute:

1. **Fork** the repository.  
2. **Clone** your fork:  
   ```bash
   git clone https://github.com/JoseLuis-Figueroa/FRDM-MCXC444-GPIO-Driver.git
   cd FRDM-MCXC444-GPIO-Driver
   ```
3. **Create a new branch** for your work:
   ```bash
   git checkout -b your-feature-branch
   ```

---

## Code of Conduct

We are committed to fostering an open, inclusive, and respectful environment.

---

## Ways to Contribute

You can contribute in many ways:

- Improve or correct documentation.  
- Fix bugs.  
- Add new reusable drivers for another peripherals.  
- Add test cases.  
- Improve examples or demos (e.g. LED/button applications).

---

## Development Setup

Make sure you have the following installed:

- MCUXpresso IDE.  
- GNU ARM Embedded Toolchain.  
- A supported board like `FRDM-MCXC444`.  

To build the project using the MCUXpresso toolbar:  
Click **"Build"** on the bottom toolbar.  

---

## Coding Standards

- Follow **MISRA-C** style guidelines wherever possible.  
- Use consistent naming and file organization.  
- Write **clean**, **modular**, and **reusable** code.  
- Add comments and **document your code** using Doxygen.

---

## Making a Pull Request

1. Make sure your code builds and passes tests.  
2. Run Doxygen to generate updated documentation (if applicable).  
3. Push your branch:
   ```bash
   git push origin your-feature-branch
   ```
4. Open a pull request on GitHub.  
5. Link the relevant issue if applicable.

---

## Commit Message Guidelines

We follow [Conventional Commits](https://www.conventionalcommits.org/):

- `feat:` New feature  
- `fix:` Bug fix  
- `docs:` Documentation only changes  
- `style:` Formatting, missing semi colons, etc  
- `refactor:` Refactoring code  
- `test:` Adding missing tests  
- `chore:` Maintenance  

**Example:**

```
feat(spi): add master-slave data sync example
```

Name the branch according to the conventional commits is another way to do it.
```
feature/Update-Contributing
```

Write the commits without conventional.
```
Add Commit Message Guidelines section.
```

---

