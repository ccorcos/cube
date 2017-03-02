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
nuclide-ocaml
nuclide-language-reason
nuclide-code-format
nuclide-type-hint
nuclide-datatip
nuclide-definition-hyperclick
```

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

## Questions

- documentation
  - macros. @@bs syntax. ## syntax
  - loading external js and re libraries
  - js browser stuff

- updater is memoized... what about partial application? is it a weak map? https://github.com/reasonml/rehydrate/blob/master/documentation.md#updater

- publishing packages
- utility packages

# To Do

- load glamor
- read rehydrate docs

- webpack dev server with htmlplugin
- typesafe inline styles
