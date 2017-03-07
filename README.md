# Sound JavaScript

I almost barfed the other day using TypeScript. I built up enough courage to go over to the dark side and try a Microsoft product. Everything seemed great. I got a Redux project up and running and when I opened up the browser... a runtime exception! The whole point of a compiler is to prevent runtime exceptions. And this is why I've decided to adventure off into the world of sound type systems.

So why not Elm or PureScript? Both languages are super cool but both have some parts I'm not as excited about. PureScript uses Bower -- ew! And neither have simple interoperability with external JavaScript libraries. I had a conversation with @chenglou and he absolutely sold me on Reason. So here we go.

## Getting Started

If you're getting started from absolutely nothing on a Mac, the following will get you set up. But it's likely you've already done this:

```sh
# install developer tools
xcode-select --install
# install homebrew
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# install node and npm
brew install node
# install atom editor
brew cask install atom
```

These are the necessary tools that are specific to Reason that you probably don't have yet:

```sh
# install ninja
brew install ninja
# install and build the reason cli tools
npm install -g git://github.com/reasonml/reason-cli.git
# install the atom editor plugin along with a bunch of other facebook tooling
apm install nuclide
```

Nuclide is going to mess with your Atom UI so you can go to Settings > Packages, search for "nuclide" and open up the Nuclide Settings.  Somewhere towards the middle is a "Use" section with a bunch of check boxes. I believe you can turn everything off except for the following:

```
hyperclick
nuclide-code-format
nuclide-datatip
nuclide-definition-hyperclick
nuclide-language-reason
nuclide-ocaml
nuclide-type-hint
```

I would got to the `nuclide-code-format` section and tick "format on save", and go to the `hyperclick` section and change the the command to `control-click` so you can still use `command-click` for multiple cursors.

At the end of the day, there are 4 editor features that you should make sure are working:
- When you add garbage syntax, there should be red lines with compile errors.
- When you hover over a variable (where you cursor isn't), a datatip shows up with the type signature.
- When you control-click on a variable, it will jump to the definition of that variable.
- When you change the whitespace in the file and hit save, everything reformats to the way it was before.

You might notice some errors in the editor already even with a fresh project. That's because the editor depends on the artifacts created by the build system. So let's get this project running:

```sh
npm install
npm start
# in another tab
npm run build
# in another tab
open src/index.html
```

## Learning Reason

Reading through the docs is an invaluable experience. Start at the [Reason homepage](http://facebook.github.io/reason/index.html) and I'd recommend reading the whole thing along with the [Modules section](http://facebook.github.io/reason/modules.html) twice. If you're coming from a JavaScript background, make sure you check out the [JavaScript comparison section](http://facebook.github.io/reason/javaScriptCompared.html).

Reason has a package called [Rehydrate](https://github.com/reasonml/rehydrate) with type definitions for React along with an custom API. You'll definitely need to read through the [Rehydrate docs](https://github.com/reasonml/rehydrate/blob/master/documentation.md).

Things to talk about:
- two modules, JSX uses `createElement` with labeled args
- the `updater` function memoizes and saves references to the underlying class
- functional style where you never actually call `setState`

With a powerful type system, its not such a pain to pass things through props.

Check out some of these examples:
https://github.com/chenglou/rehydrate-example/tree/master/src

Read about bucklescript since we're using that to compile OCaml => JS.
https://github.com/bloomberg/bucklescript
https://bloomberg.github.io/bucklescript/Manual.html
