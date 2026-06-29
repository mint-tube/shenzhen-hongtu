# SHENZHEN HONGTU ELECTRONICS CO., LTD.
**───── A manual for new employees ─────**

### Two interfaces. Limitless possibilities.

- **Pipe**
> Pipes asynchronously transmit 16-bit values. When a value is moved into a pipe from one end, it will be stored on the other end until it is overwritten. Reading does not change the value. Writing to a Pipe port will only affect the value stored on the other end.

- **XBus**
> XBus synchronously transmits discrete 2-byte packets. It has no buffer, so if one port attempts to read or write, it will be suspended until the other port makes a corresponding operation.

*Note: both interfaces are one-to-one and work symmetrically. Use DS/xx components to create other types of connections.*

## HTxxx microcontroller Family

HTxxx is a family of 16-bit microcontrollers employing a common programming language. A program written for one member of the HTxxx family can be re-used in any other HTxxx microcontroller with few or no changes, though HTxxx microcontrollers have varying features and pinouts which may create implementation differences.

### Language Reference

#### Program Structure
Each line of an HTxxx program must have the following structure: 
`LABEL CONDITION INSTRUCTION COMMENT`.
All parts are optional, but must appear in the specified order if present. Example of a syntactically valid program:
```
# This is a comment.
loop: # until r0 is ten
  teq r0 10
+ jmp end
  mov 50 x2
  add 1
  jmp loop
end:
 mov 0 r0 # reset counter
```

#### Comments
Any text following a `#` is ignored until the end of the line.

#### Labels
Labels must appear first on a line and are followed by `:`. Labels are used as jump targets and must begin with a letter.

#### Conditional Execution
All instructions in the HTxxx programming language are capable of conditional execution. Prefixing an instruction with a `+` or `-` symbol will cause that instruction to be enabled or disabled by the last executed test instruction.  
Instructions that are disabled by a test instruction will be skipped. All conditional instructions start in a disabled state.

See `Example Circuit: Complex Conditions` for a usage example.

#### Execution order
Every step of execution, all microcontrollers that are not yet suspended by `slp` or XBus execute one line of their program. Upon reaching the end of the code, microcontroller will loop back to the first line without resetting its state. Lines with no instruction are skipped.

#### Registers
Registers are used as sources and destinations for data manipulated with instructions. The set of registers varies between different microcontrollers.

- `r0` is the primary general-purpose register used for internal computation on the microcontrollers. Arithmetic operations use and modify the value of `r0`.
- `r1`, `r2`, etc. are other general-purpose registers available on some HTxxx family members.
- `p0`, `p1`, `x0`, `x1`, etc. are pin registers, which are used when reading from or writing to the pins of a microcontroller. Pins starting with `p` function as Pipe interfaces and the ones with `x` implement the XBus protocol.

All registers of the HTxxx microcontrollers are initialized with 0.

#### Operands
Each type of instruction requires a fixed number of operands. Operands must appear following the instruction name, separated by spaces. Instruction operands are described with the following notation:

Notation | Meaning                         
-------- | --------------------------------
R        | Any register                    
I        | Integer between -32768 and 32767
R/I      | Register or integer             
L        | Label                           

Binary and hexadecimal integers can be written using 0b and 0x prefixes respectively.

#### Basic instructions
- `nop`  
  This instruction has no effect, but will take a cycle to execute

- `mov R/I R`  
  Copy the value of the first operand into the second operand.

- `swp R R`  
  Swap the values in specified registers.

- `jmp L`  
  Jump to the line where the specified label is located.

- `slp R/I`  
  Suspend execution until all chips are suspended. Repeat the specified number of times.

#### Arithmetic and bitwise instructions
Internal registers are 16-bit and store signed integer values between -32768 and 32767 inclusive in two's complement. If overflow or underflow would occur, the value will be clamped in a supported range

These instructions use the value in `r0` as their first operand and store the result in it:

Instruction | Action                         
--------    | --------------------------------
`add R/I`   | r0 = r0 + ...             
`sub R/I`   | r0 = r0 − ... 
`mul R/I`   | r0 = r0 × ...
`neg`       | r0 = -r0          
`not`       | r0 = ~r0
`and R/I`   | r0 = r0 ∧ ...
`or  R/I`   | r0 = r0 ∨ ...
`xor R/I`   | r0 = r0 ⊕ ...

These instructions work with any general-purpose register:

Instruction | Action                         
--------    | --------------------------------
`inc R`     | rN = rN + 1
`dec R`     | rN = rN - 1
`clr R`     | rN = 0
  
#### Test instructions
- `teq R R/I`  
  Condition        | Effect on `+` | Effect on `-`
  ---------------- | ------------- | -------------
  A is equal to B  | **Enabled**   | Disabled     
  A not equal to B | Disabled      | **Enabled**  

- `tgt R R/I`  
  Condition            | Effect on `+` | Effect on `-`
  -------------------- | ------------- | -------------
  A is greater than B  | **Enabled**   | Disabled     
  A not greater than B | Disabled      | **Enabled**  

- `tlt R R/I`  
  Condition         | Effect on `+` | Effect on `-`
  ----------------- | ------------- | -------------
  A is less than B  | **Enabled**   | Disabled     
  A not less than B | Disabled      | **Enabled**  

- `tcp R R/I`  
  Condition           | Effect on `+` | Effect on `-`
  ------------------- | ------------- | -------------
  A is greater than B | **Enabled**   | Disabled     
  A is equal to B     | Disabled      | Disabled     
  A is less than B    | Disabled      | **Enabled**


## Parts Datasheet

### HT300
A reduced-functionality microcontroller, the HT300 is a versatile alternative to its larger cousins.

- (64) lines of program memory
- (3) registers (`r0`, `r1`, `r2`)
- (2) XBus pins (`x0`, `x1`)
- (2) Pipe pins (`p0`, `p1`)

### HT500
The workhorse of the family: balancing performance and cost with more memory and registers than HT300.

- (128) lines of program memory
- (4) registers (`r0`, `r1`, `r2`, `r3`)
- (4) XBus pins (`x0`, `x1`, `x2`, `x3`)
- (2) Pipe pins (`p0`, `p1`)

### HT700
Offering maximum power and an enormous 256-line program memory so you can minimize the chip count, the HT700 will power even your most demanding embedded applications!

- (256) lines of program memory
- (6) registers (`r0`, `r1`, `r2`, `r3`, `r4`, `r5`)
- (6) XBus pins (`x0`, `x1`, `x2`, `x3`, `x4`, `x5`)
- (2) Pipe pins (`p0`, `p1`)

### DX/2 Transformer
Control the world with the DX/2 digital I/O transformer! This unique part will make an XBus port work like a Pipe one!

Insert this device between an XBus port and a Pipe one. DX/2 will imitate the behaviour of a normal Pipe connection by storing the values written to it and being ready to read or write at all times.

### DX/5 Transformer
Lack Pipe pins but still need an unblocking I/O interface? Use DX/5 to prevent an XBus port from being blocked!

Insert this device between two XBus ports. Instead of suspending one port until the other one makes a corresponding operation, DX/5 will immediately return -32768 if there is no new packet to read or save the value to its internal buffer until the other port is ready to read it. The buffer can be assumed to be infinitely large.

// See `Example Circuit: Unblocking XBus` for a usage example

### DS/14 Splitter
With this Pipe signal splitter, you won't need to waste a whole chip just to transfer data from one port to four others!

Values written into `p0` can be read from any of the ports `s0`...`s3`. Values written into the `sN` ports will only be passed into the `p0` port.

<!-- ### DB/4P Broadcast Channel -->

### 218R-16 RAM
**218R-16** random-access memory offers embedded system engineers additional storage with a whopping 256 16-bit memory cells. With its convenient auto-increment feature, you won’t have to waste precious registers keeping track of memory addresses.

Usage:
- Memory pointers can be read and written with the `a0` and `a1` XBus pins.
- The value referenced by respective pointer can be read and written over XBus with the `d0` and `d1` pins. 
- After reading from or writing to a data pin, the corresponding memory pointer will *automatically* increment, wrapping to the first cell if necessary.

### 108R-16 ROM
**108R-16** read-only memory offers embedded system engineers access to 256 pre-set 16-bit memory cells. With its convenient auto-increment feature, you won’t have to waste precious registers keeping track of memory addresses.

Usage:
- Memory pointer can be read and written with the `a0` XBus pin.
- The value at corresponding address can be read over XBus with the `d0` pin.
- After reading from `d0`, the memory pointer will *automatically* increment, wrapping to the first cell if necessary.

### DT6060 Clock
**Key Features:**
1. Pipe signal at `m0` corresponds to the number of *minutes* that passed since midnight.
2. Pipe signal at `s0` corresponds to the number of *seconds* that passed since the beginning of this minute.

The values are updated automatically every second.

**Example Output:**  
At 03:18:37, `m0 = 198` and `s0 = 37`.

### B1P-1 Button
User input has never been simpler!  
Pipe port `b0` yields 100 when the button is pressed and 0 when it's not.

### B2X-8 Button Array
- A button array controller with generous 8 buttons!
- Read from `c0` and `c1` XBus pins to fetch the next event. `-999` will be returned if no new events occurred yet.

Direction | Value     | Meaning
--------- | --------- | -------------------
Read      | [button]  | [button] pressed
Read      | -[button] | [button] released

### LX3D Number Display
- Numerical display with 3 digits and a minus sign
- Write to the `d0` Pipe pin to display integer values from -999 to 999.

Example (-387):
```
░░░░████░████░████  
░░░░░░░█░█░░█░░░░█  
███░████░████░░░░█  
░░░░░░░█░█░░█░░░░█  
░░░░████░████░░░░█  
```

### LX256S 16x16 Display
A convenient 16x16 display, now with integrated touchscreen controller!

Pin  | Direction | Value       | Meaning                          
---- | --------- | ----------- | ---------------------------------
`a0` | Write     | [id]/-[id]  | Turn on/off segment no. [id]  
`a0` | Write     | 999/-999    | Turn on/off all segments
`t0` | Read      | [id]        | The last touched segment is [id]
`q0` | Write     | [id]        | Query segment no. [id]'s state
`q0` | Read      | 1/0         | Last queried segment is on/off

The [id]s are counted from the top-left corner, so (x; y) has id = 16y + x.  
`t0` is -999 until first interaction, all segments are off by default.

### MC20X0 Math Co-processor
MC20X0 is a versatile math co-processor.  
Write a **command sequence** to either `c0` or `c1` XBus pin to perform a calculation - every part of it must be a separate XBus packet.  
Once a complete **command sequence** is written to the pin, the value in it will be overwritten with the result of the specified calculation. Reading the result does not reset it.

List of command sequences:
Operation   | Input  | Result      
----------- | ------ | -------------------
Echo        | 10 A   | A
Add         | 20 A B | A + B
Subtract    | 30 A B | A − B
Multiply    | 40 A B | A × B
Divide      | 50 A B | floor(A / B)
Remainder   | 60 A B | A % B
Power       | 70 A B | floor(pow(A, B))
Square root | 80 A   | floor(sqrt(A))
Min         | 91 A B | Smaller of the numbers
Max         | 92 A B | Larger of the numbers

*Note: Division by zero and square root of a negative number will result in `0`.*

### RNG2 Random Number Generator
This random number generator will produce a new value every cycle! Use pipe port `v0` to get a random positive number or `v1` to get any number in the full 16-bit range.

## Breadboard Description

In Shenzhen Hongtu Electronics, we use a standardized format to depict the parts and connections between them. This part of the manual will tell you everything about it.

First, create a new folder. Create a file with extension `.top`.  
This file depicts the **topology** of your breadboard - what parts do you use and how their pins are connected. The format is very human:
```
# The file begins with the length of one instruction cycle and the additional delay after `slp` instruction. Both in milliseconds.
cycle = 10
sleep = 20

# Then, a list of used parts and their nicknames.
MC20X0 math
HT500 chip
LX3D display

# Afterwards, list all connections between those parts. The order doesn't matter. DX/x devices need to be mentioned between the hyphens here.
math::c0 - chip::x0
chip::x1 - DX/2 - display::q0

# As you may have noticed, any text after `#` is considered a comment
```

Some parts require additional configuration. Put their code in a file with the same name as their nickname in the same directory as the topology file.

**HTxxx:** the code for the microcontroller  
**108R-16:** 256 groups of 2 hex digits separated with any whitespace symbols - the initial state of the cells.  
**B1P-1:** a string with at most 9 characters - the label on the button  
**B2X-8:** 8 strings with at most 4 characters separated with newlines - the labels on the buttons

## Example Circuits
-----WIP-----