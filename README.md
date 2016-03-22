# EOH-Badge-2016
Badges made to hand out as a teaching exercise for the IEEE UIUC exhibit at Engineering Open House 2016. When you cover up the light sensor, the badges play along and flash to "Hail to the Orange". You can see a video of the build in action [here](https://www.youtube.com/watch?v=S4cmx-UWJ_Q&feature=youtu.be). This exhibit won second place in the "Just for Fun" category!

Special thanks to [David Mellis](http://web.media.mit.edu/~mellis/) for his [attiny library](https://github.com/damellis/attiny).

# Media
![Finished product](http://i.imgur.com/lHmo0eT.jpg?1)

You can see a video of the exhibit in action, as well as IEEE's other exhibits [here](https://www.youtube.com/watch?v=S4cmx-UWJ_Q&feature=youtu.be).

Some excellent photos taken by Ray Chan during EOH [here](https://photos.google.com/share/AF1QipN_tZymQB7QjqU8kMJ0lrtPr13E5zKEWU58SieGECw1yZU4zlcl4fVr3wqzv2gzeQ?key=Mm0zcS1icEtFYU44bktMVk84OHpqdEVZcEROZm53)

# Bugs
- Orange and Blue LED are labeled backwards, whoops!
- The 500kOhm resistor is far too large, 50k would be much better. Typo from reading the datasheet, just makes the devices extremely sensitive. 
- First note is always wrong, probably need to re-read Timer init code
- Lanyard hole is slightly too small, +5-10 mils would be better
- My initials are covered up the battery cover (this one was actually intended)
