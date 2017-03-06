# Sound JavaScript

I almost barfed the other day using TypeScript. I built up enough courage to go over to the dark side and try a Microsoft product. Everything seemed great. I got a Redux project up and running and when I opened up the browser... a runtime exception! The whole point of a compiler is to prevent runtime exceptions. And this is why I've decided to adventure off into the world of sound type systems.

So why not Elm or PureScript? Both languages are super cool but both have some parts I'm not as excited about. PureScript uses Bower -- ew! And neither have nice interoperability with external JavaScript libraries. I had a conversation with @chenglou and he absolutely sold me on Reason. So here we go.

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

Nuclide is going to mess with your Atom UI a ton so open up Settings > Packages and open up the Nuclide Settings. Somewhere towards the middle is a "Use" section with a bunch of check boxes. You can turn everything off except for the following:

```
hyperclick
nuclide-code-format
nuclide-datatip
nuclide-definition-hyperclick
nuclide-language-reason
nuclide-ocaml
nuclide-type-hint
```

Verify the following things are working:
- When you delete a semicolon, there are red lines and compile error warnings.
- When you hover over a variable, a datatip shows up with the type signature.
- When you change the whitespace in the file and hit save, everything reformats to the way it was before.
- When you control-click (or command-click) on a variable, it will jump to the definition of that variable.

And now to actually get this project running:

```sh
npm install
npm start
# in another tab
npm run build
# in another tab
open src/index.html
```

## Reading

http://facebook.github.io/reason/javaScriptCompared.html

http://facebook.github.io/reason/index.html

http://facebook.github.io/reason/modules.html
