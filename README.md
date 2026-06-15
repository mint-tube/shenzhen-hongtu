# SHENZHEN HONGTU ELECTRONICS CO., LTD.
**───── A manual for new employees ─────**

### Two interfaces. Limitless possibilities.

- **Pipe**
> Pipes asynchronously transmit 2-byte values. When a value is moved into a pipe from one end, it will be stored on the other end until it is overwritten (reading does not affect the value).

- **XBus**
> XBus synchronously transmits discrete 2-byte packets. It has no buffer, so if one port attempts to read or write, it will be suspended until the other port makes a corresponding operation.

*Note: both interfaces are one-to-one and work symetrically. Use DS/xx components to create other types of connections.*

## HTxxx Microprocessor Family

HTxxx is a family of 16 bit microcontrollers employing a common programming language. A program written for one member of the HTxxx family can be re-used in any other HTxxx microcontroller with few or no changes, though HTxxx microcontrollers have varying features and pinouts which may create implementation differences.

### Language Reference

#### Program Structure
Each line of an HTxxx program must have the following structure: 
`LABEL CONDITION INSTRUCTION COMMENT` 
All components are optional, but must appear in the specified order if present. Examples of syntactically valid code:
```
# This is a comment.
loop: # until ACC is ten
 teq acc 10
+ jmp end
 mov 50 x2
 add 1
 jmp loop
end:
 mov 0 acc # reset counter
```

#### Comments
Any text following a “#” symbol is ignored until the end of the line.

#### Labels
Labels must appear first on a line, and are followed by a colon (":"). Labels are used as jump targets and must begin with a letter and may contain alphabetic, numeric, and underscore characters.

#### Conditional Execution
All instructions in the HTxxx programming language are capable of conditional execution. Prefixing an instruction with a `+` or `-` symbol will cause that instruction to be enabled or disabled by the last executed test instruction.  
When an instruction is disabled by a test instruction, it will be skipped. All conditional instructions start in a disabled state.

// See `Example Circuit: Complex Conditions` for a usage example.

#### Execution order
Every step of execution all microprocessors that are not yet `slp`ing or are suspended by XBus execute one line of their program. After reaching the end of the code, microcontroller will loop back to the first line without reseting its state. Programmers may assume that instruction other than `slp` take no time to execute.

#### Registers
Registers are used as sources and destinations for data manipulated with instructions. The set of registers varies between different microcontrollers.

- `acc` is the primary general-purpose register used for internal computation on the microcontrollers. Arithmetic operations use and modify the value of acc.
- `dat` and `aux` are another general-purpose registers available on some HTxxx family members.
- `p0`, `p1`, `x0`, `x1`, `x2` and etc. are pin registers, which are used when reading from or writing to the pins of a microcontroller. Pins starting with `p` function as Pipe interfaces and `x` ones implement the XBus protocol.

All registers of the HTxxx microprocessors are initialized with 0.

#### Operands
Each type of instruction requires a fixed number of operands. Operands must appear following the instruction name, separated by spaces. Instruction operands are described with the following notation:

Notation | Meaning                         
-------- | --------------------------------
R        | Any register                    
I        | Integer between -32768 and 32767
R/I      | Register or integer             
L        | Label                           

Integers can also be written in binary or hexadecimal number systems using prefixes 0b and 0x.

#### Basic instructions
- `nop`  
  This instruction has no effect.

- `mov R/I R`  
  Copy the value of the first operand into the second operand.

- `swp R R`  
  Swap the values in specified registers.

- `jmp L`  
  Jump to the line where the specified label is located.

- `slp R/I`  
  Sleep for the number of ticks specified by the operand.

#### Arithmetic instructions
Registers can store integer value between -32768 and 32767 inclusive. If an arithmetic operation would produce a result outside this range, overflow or underflow will occur.

- `add R/I`   
  Add the value to `acc` and store the result in `acc`.

- `sub R/I`  
  Subtract the value from `acc` and store the result in `acc`.

- `mul R/I`  
  Multiply the value by `acc` and store the result in `acc`.

- `not`  
  If the value in `acc` is 0, put 1 in `acc`. Otherwise, put 0 in `acc`.

- `neg`  
  Change the sign of the value in `acc`.

#### Bitwise instructions
All registers are 16 bit wide. Integers are represented using two`s complement.

- `and R/I`  
  Bitwise AND the value with `acc` and store the result in `acc`.

- `xor R/I`  
  Bitwise XOR the value with `acc` and store the result in `acc`.
  
#### Test instructions
- `teq R/I R/I`  
  Condition        | Effect on `+` | Effect on `-`
  ---------------- | ------------- | -------------
  A is equal to B  | **Enabled**   | Disabled     
  A not equal to B | Disabled      | **Enabled**  

- `tgt R/I R/I`  
  Condition            | Effect on `+` | Effect on `-`
  -------------------- | ------------- | -------------
  A is greater than B  | **Enabled**   | Disabled     
  A not greater than B | Disabled      | **Enabled**  

- `tlt R/I R/I`  
  Condition         | Effect on `+` | Effect on `-`
  ----------------- | ------------- | -------------
  A is less than B  | **Enabled**   | Disabled     
  A not less than B | Disabled      | **Enabled**  

- `tcp R/I R/I`  
  Condition           | Effect on `+` | Effect on `-`
  ------------------- | ------------- | -------------
  A is greater than B | **Enabled**   | Disabled     
  A is equal to B     | Disabled      | Disabled     
  A is less than B    | Disabled      | **Enabled**  

## Parts Datasheet

### HT300
A reduced-functionality microcontroller, the HT300 is a versatile alternative to its larger cousins, HT500 and HT700.

- (16) lines of program memory
- (1) general-purpose register (`acc`)
- (2) XBus pins (`x0`, `x1`)
- (2) Pipe pins (`p0`, `p1`)

### HT500
The workhorse of the family: balancing performance and cost with double the memory and registers of the HT300.

- (32) lines of program memory
- (2) general-purpose register (`acc`, `dat`)
- (4) XBus pins (`x0`, `x1`, `x2`, `x3`)
- (2) Pipe pins (`p0`, `p1`)

### HT700
Offering maximum power and an enormous 64-line program memory so you can minimize the chip count, the HT700 will power even your most demanding embedded applications!

- (64) lines of program memory
- (3) general-purpose register (`acc`, `dat`, `aux`)
- (6) XBus pins (`x0`, `x1`, `x2`, `x3`, `x4`, `x5`)
- (2) Pipe pins (`p0`, `p1`)

### DX/2 Transformer
Control the world with the DX/2 digital I/O transformer! This unique and useful part will cause a XBus port to work like a Pipe one!

Insert this device between an XBus port and a Pipe one. DX/2 will imitate the behaviour of a normal Pipe connection by storing the values written to it and being ready to read or write at all times.

### DX/5 Transformer
Lack Pipe pins but still need an unblocking I/O interface? Use DX/5 to prevent an XBus port from being blocked!

Insert this device between two XBus ports. Instead of suspending one port until the other one makes a corresponding operation, DX/5 will immediately return -999 if there is no new packets to read or save the value to its internal buffer if the other port is not ready to read it. The buffer can be assumed to be infinitely large.

// See `Example Circuit: Unblocking XBus` for a usage example

### DS/14 Splitter
With this Pipe signal splitter, you won't need to waste a whole chip just to transfer data from one port to two others!

Values written into the `w0` can be read from any of the port from `r0` to `r3`. Values written into the `rN` ports will only be passed into the `w0` port.

### 100P-16 RAM
**100P-16** random-access memory by Pingda Co., Ltd. offers embedded system engineers additional storage with a whopping sixteen 16-bit memory cells. With its convenient auto-increment feature, you won’t have to waste precious registers keeping track of memory addresses.

- (16) random-access memory cells
- (2) independent, auto-incrementing memory pointers

Usage:
- All memory cells and pointers are initialized to 0.
- Memory pointers can be read and written over XBus with the `a0` and `a1` pins.
- Memory values referenced by pointers can be read and written over XBus with the `d0` and `d1` pins. 
- After reading from or writing to a data pin, the corresponding memory pointer will *automatically* increment, wrapping to the first cell if necessary.

### 200P-16 ROM
**200P-16** read-only memory by Pingda Co. Ltd. offers embedded system engineers the ability to easily access up to sixteen factory-programmed memory cells. With its convenient auto-increment feature, you won’t have to waste precious registers keeping track of memory addresses.

- (16) random-access read-only memory cells
- (2) independent, auto-incrementing memory pointers

Usage:
- All memory pointers are initialized to 0.
- Memory pointers can be read and written over XBus with the `a0` and `a1` pins.
- Memory values referenced by pointers can be read over XBus with the `d0` and `d1` pins. 
- After reading from a data pin, the corresponding memory pointer will *automatically* increment, wrapping to the first cell if necessary.

### DT6060 Clock
**Key Features:**
1. Emits a Pipe signal at `m0` that corresponds to the number of *minutes* that passed since midnight.
2. Emits a Pipe signal at `s0` that corresponds to the number of *seconds* that passed since the beginning of this minute.

The values are updated automatically every second.

**Example Output:**  
At 01:19:37, `m0 = 79`, `s0 = 37`.

### B1PB-1 Button
User input has never been simpler!  
Pipe port `b0` yields 100 when the button is pressed and 0 when it's not.

### B2PB-8 Button Array
- A XBus button array controller with generous 8 buttons!
- Use the `c0` and `c1` XBus pins to poll for events.

Direction | Value     | Meaning
--------- | --------- | -------------------
Read      | [button]  | [button] down event
Read      | -[button] | [button] up event

### LX7D Number Display
- 7-segment numerical display with 3 digits and a minus sign
- Write to the `d0` Pipe pin to display integer values from -999 to 999.

Example (-387):
```
░░░░████░████░████  
░░░░░░░█░█░░█░░░░█  
███░████░████░░░░█  
░░░░░░░█░█░░█░░░░█  
░░░░████░████░░░░█  
```

### LX64S 8x8 Display
A convenient 8x8 display, now with integrated touchscreen controller!

Pin  | Direction | Value       | Meaning                          
---- | --------- | ----------- | ---------------------------------
`a0` | Write     | [id]/-[id]  | Turn on/off segment no. [id]  
`a0` | Write     | 999/-999    | Turn on/off all segments
`t0` | Read      | [id]/-[id]  | Segment no. [id] pressed/released    
`q0` | Write     | [id]        | Query segment no. [id]'s state
`q0` | Read      | 1/0         | Last queried segment is on/off

*Note: the [id]s are the following:*
```
01 02 03 04 05 06 07 08
09 10 11 12 13 14 15 16
17 18 19 20 21 22 23 24
25 26 27 28 29 30 31 32
33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48
49 50 51 52 53 54 55 56
57 58 59 60 61 62 63 64
```
Or just `8y + x` counting from the top-left corner.

### MC20X0 Math Co-processor
MC20X0 is a versatile math co-processor.  
Write a **command sequence** to either `c0` or `c1` XBus pin to perform a calculation.  
Once a complete **command sequence** is written to the pin, the value in it will be overwritten with the result of the specified calculation. Reading the result does not clear it.

List of command sequences :
Operation   | Input  | Result      
----------- | ------ | -------------------
Echo        | 10 A   | A
Add         | 20 A B | A + B
Subtract    | 30 A B | A - B
Multiply    | 40 A B | A * B
Divide      | 50 A B | floor(A / B)
Remainder   | 60 A B | A % B
Power       | 70 A B | floor(pow(A, B))
Square root | 80 A   | floor(sqrt(A))
Min         | 91 A B | Smaller of the numbers
Max         | 92 A B | Larger of the numbers

*Note: Division by zero and square root of a negative number will result in `0`.*

### RNG2 Random Number Generator
This random number generator will produce a new value every tick! Use pipe ports `r0` to get a random positive number or `r1` to get any number in the full 16-bit range.

## Breadboard Description

In Shenzhen Hongtu Electronics, we use a standardized format to depict the parts and connections between them. This part of manual will tell you everything about it.

First, create a new folder. Create a file with extension `.top`.  
This file depicts the *topology* of you breadboard - what parts do you use and how their pins are connected. The format is pretty intuitive:

```
# This file must begin with the length of one `slp` tick (in ms).
tick = 100

# Then, a list of used parts and their nicknames (any symbols).
MC20X0 math
HT500 chip
LX64S display

# Afterwards, list all the connections between those parts. The order doesn't matter. DX/x devices need to be metioned between hyphens here.
math::c0 - chip::x0
chip::x1 - display::a0
chip::x2 - display::t0
chip::p0 - DX/2 - display::q0

# As you may have noticed, any text after `#` is ignored until the end of the line.
```

The code for HTxxx devices is stored in separate files with a `.hts` extension. For example, `chip.hts` would be the code for the `chip` microcontroller.

## Example Circuits
-----WIP-----

## Advice for new employees
- Don't forget to `slp`!
- You can change the length of one `slp` tick.
- If something isn't explicitly mentioned in these documents - it's implementation-specific.
- Consider using HT300 and HT500 - you may not need the capabilities of HT700.
- Reading from LX64S'`t0`, B2PB-8'`c0` and etc. **will suspend the chip** until an event occurs.