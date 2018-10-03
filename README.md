
# Table of Contents

1.  [DreamCell CPU design [2016 .. ongoing]](#org65457a1)
    1.  [Instructions](#org17260a0)
        1.  [row broadcast](#orga39d11f)
        2.  [column broadcast](#orgb647c88)
        3.  [cell register](#orgd40d272)
        4.  [neighbor communication?](#orgbce4979)
    2.  [Some abstractions are an unaffordable luxery](#org0a4c42f)
    3.  [Waiting for technology that doesn't exist yet](#orgc48a334)
        1.  [massive bandwidth](#org41fa94c)
    4.  [Philosophy](#orgadb9faa)
        1.  [General purpose processor](#orga8cbbda)
        2.  [Simulating on JADE](#org8249f8b)



<a id="org65457a1"></a>

# DreamCell CPU design [2016 .. ongoing]


<a id="org17260a0"></a>

## Instructions

-   What kind of instructions are there? permutations.


<a id="orga39d11f"></a>

### row broadcast


<a id="orgb647c88"></a>

### column broadcast


<a id="orgd40d272"></a>

### cell register


<a id="orgbce4979"></a>

### neighbor communication?

-   charts, map, atlas - reuse terminology.


<a id="org0a4c42f"></a>

## Some abstractions are an unaffordable luxery


<a id="orgc48a334"></a>

## Waiting for technology that doesn't exist yet


<a id="org41fa94c"></a>

### massive bandwidth

possible configuration of large sections of the chip every clock cycle.

how to fill all blocks


<a id="orgadb9faa"></a>

## Philosophy


<a id="orga8cbbda"></a>

### General purpose processor

-   no specialized units.
-   reconfigurable regions finer grained than FPGA
-   Scalable congruent region configurations, a 2x2 function block has
    the same configuration as a 4x4 function block. They perform the
    same function, only differing in the width of the input.

-   Localized data into regions, like a patch space.


<a id="org8249f8b"></a>

### Simulating on JADE

clone the current register device and set the cap to 0, risetime to 0.
the bus will for an N\*N cell there will be a N-wide bus for each row.

