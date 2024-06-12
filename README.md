Instructions:

1. Clone the repo with submodules `git clone --recursive https://github.com/mthierman/example-juce-gain-plugin-webview.git`
2. Install [Node.js](https://nodejs.org/en)
3. Run `npm install` to install [Vite](https://vitejs.dev/) and the JUCE frontend framework
4. Run `npm run dev` to run the Vite [development server](http://localhost:5173/)
5. Run `npm run cmake` or `cmake -S . -B build && cmake --build build` to build the project

The project will use the development server in debug mode and will load `index.html` from JUCE's BinaryData in release mode.
