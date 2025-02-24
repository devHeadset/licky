

-----------------------------------------------------------------------------

Using .txt because, too bored to make a .md.

Licky is a simple C++ tool that fetches and shows the lyrics of a given song,
Its pretty straightforward (how to use it, I mean), but a simple tutorial:

So let's say, I want to read the lyrics of "Strangers in the Night" by Frank
Sinatra, 

❯ ./licky \
      --artist "Frank Sinatra" \
      --song "Strangers in the Night"

Strangers in the night exchanging glances
Wond'ring in the night what were the chances
We'd be sharing love before the night was through
Something in your eyes was so inviting
Something in you smile was so exciting
[...]

Though, sadly, the API that licky uses is *very* simple, so a few songs
are missing their bits & pieces of their lyrics.
I do plan on changing the api, and also adding a sort of sync with ncspot,
but that will be in a later date.

I will, however, add a TODO section on this readme, for features that I plan
to add. Even though this was meant to be a simpler tool.

------------------------------- Compiling -----------------------------------

So, if you wish to compile from source, instead of downloading the pre-compiled
binary, you will need to install ncurses-devel, curl-devel and my own library,
clicky.

For those two, ncurses and curl, you can easily install both (in Fedora linux)
with:

sudo dnf install -y ncurses-devel curl-devel

But, clicky, you'll have to do that by yourself (don't worry, I explain how to
build the library on the repo https://auth-xyz.github.io/clicky)

---------------------------------- TODO -------------------------------------

[ ] - to implement
[x] - finished implementing

----------------------------

[ ] : Change to a better API
[ ] : Either add an already existing algorithm for lyrics matching or make one
[ ] : Add some sort of sync with ncspot


