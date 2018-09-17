#!/usr/bin/env perl
use FileHandle;
use Data::Dumper;
sub keymap {
$cell  = '------------------';
$space = '                  ';
print qq(Keymap: $_[76]

 ,$cell-$cell-$cell-$cell-$cell-$cell-$cell.                ,$cell-$cell-$cell-$cell-$cell-$cell-$cell.
 |$_[0]|$_[1]|$_[2]|$_[3]|$_[4]|$_[5]|$_[6]|                |$_[7]|$_[8]|$_[9]|$_[10]|$_[11]|$_[12]|$_[13]|
 |$cell+$cell+$cell+$cell+$cell+$cell+$cell|                |$cell+$cell+$cell+$cell+$cell+$cell+$cell|
 |$_[14]|$_[15]|$_[16]|$_[17]|$_[18]|$_[19]|$_[20]|                |$_[21]|$_[22]|$_[23]|$_[24]|$_[25]|$_[26]|$_[27]|
 |$cell+$cell+$cell+$cell+$cell+$cell|$space|                |$space|$cell+$cell+$cell+$cell+$cell+$cell|
 |$_[28]|$_[29]|$_[30]|$_[31]|$_[32]|$_[33]|$cell|                |$cell|$_[36]|$_[37]|$_[38]|$_[39]|$_[40]|$_[41]|
 |$cell+$cell+$cell+$cell+$cell+$cell|$_[34]|                |$_[35]|$cell+$cell+$cell+$cell+$cell+$cell|
 |$_[42]|$_[43]|$_[44]|$_[45]|$_[46]|$_[47]|$space|                |$space|$_[48]|$_[49]|$_[50]|$_[51]|$_[52]|$_[53]|
 \`$cell+$cell+$cell+$cell+$cell+$cell+$cell'                \`$cell+$cell+$cell+$cell+$cell+$cell+$cell'
 |$_[54]|$_[55]|$_[56]|$_[57]|$_[58]|                                                                                            |$_[59]|$_[60]|$_[61]|$_[62]|$_[63]|
 \`$cell-$cell-$cell-$cell-$cell'                                                                                            \`$cell-$cell-$cell-$cell-$cell'
                                                                                                  ,$cell-$cell.            ,$cell-$cell.
                                                                                                  |$_[64]|$_[65]|            |$_[66]|$_[67]|
                                                                               ,$cell|$cell|$cell|            |$cell+$cell+$cell.
                                                                               |$space|$space|$_[70]|            |$_[71]|$space|$space|
                                                                               |$_[68]|$_[69]|$cell|            |$cell|$_[72]|$_[73]|
                                                                               |$space|$space|$_[74]|            |$_[75]|$space|$space|
                                                                               \`$cell-$cell-$cell'            \`$cell-$cell-$cell'

);
}

sub pad{
  $_=~s/^\s+//;
  $_=~s/\s+$//;
  $key = $_;
  return "        ø         " if $key eq "KC_TRNS";
  return "                  " if $key eq "KC_NO";
  $key=~s/^KC_//;
  $l = length($key);
  $pad = 18 - $l;
  $before_padding = "";
  $after_padding = "";
  for($i = 0; $i < int($pad/2); $i++){ $before_padding.=" "};
  for($j = 0; $j < int( ($pad/2) + 0.5); $j++){ $after_padding.=" "};
  return $before_padding.$key.$after_padding
}

sub split2wide {
  my @s;
  (
    $s[0],  $s[1],  $s[2],  $s[3],  $s[4],  $s[5],  $s[6],
    $s[14], $s[15], $s[16], $s[17], $s[18], $s[19], $s[20],
    $s[28], $s[29], $s[30], $s[31], $s[32], $s[33],
    $s[42], $s[43], $s[44], $s[45], $s[46], $s[47], $s[34],
    $s[54], $s[55], $s[56], $s[57], $s[58],
                                            $s[64], $s[65],
                                                    $s[70],
                                    $s[68], $s[69], $s[74],

    $s[7],  $s[8],  $s[9],  $s[10], $s[11], $s[12], $s[13],
    $s[21], $s[22], $s[23], $s[24], $s[25], $s[26], $s[27],
    $s[36], $s[37], $s[38], $s[39], $s[40], $s[41],
    $s[35], $s[48], $s[49], $s[50], $s[51], $s[52], $s[53],
    $s[59], $s[60], $s[61], $s[62], $s[63],
            $s[66], $s[67],
                    $s[71],
    $s[75], $s[72], $s[73]) = (@_);

    map { $_ = pad($_); } @s;
    return @s;
}

sub psplit{
  my $split_char = shift;
  my $line  = shift;
  my @items;
  my @arrayline = split(//,$line);
  my $buffer = "";
  my $inside_parens = 0;
  for( my $char = 0; $char < length($line); $char ++){

    if($arrayline[$char] eq '('){ $inside_parens = 1; }
    if($arrayline[$char] eq ')'){ $inside_parens = 0; }
    if($arrayline[$char] eq $split_char){
      if ($inside_parens == 0){
        push(@items,$buffer);
        $buffer = "";
      }else{
        $buffer.=$arrayline[$char];
      }
    }else{
      $buffer.=$arrayline[$char];
    }
  }
  push(@items,$buffer);
  return @items;
}

################################################################################

# keymap ("LH00", "LH01", "LH02", "LH03", "LH04", "LH05", "LH06",                   "RH00", "RH01", "RH02", "RH03", "RH04", "RH05", "RH06",
#         "LH10", "LH11", "LH12", "LH13", "LH14", "LH15", "LH16",                   "RH10", "RH11", "RH12", "RH13", "RH14", "RH15", "RH16",
#         "LH20", "LH21", "LH22", "LH23", "LH24", "LH25", "LH26",                   "RH20", "RH21", "RH22", "RH23", "RH24", "RH25", "RH26",
#         "LH30", "LH31", "LH32", "LH33", "LH34", "LH35",                                   "RH31", "RH32", "RH33", "RH34", "RH35", "RH36",
#         "LH40", "LH41", "LH42", "LH43", "LH44",                                                   "RH42", "RH43", "RH14", "RH45", "RH46",
#                                                         "LH51", "LH52",   "RH50", "RH51",
#                                                 "LH60", "LH61", "LH62",   "RH60", "RH61", "RH62",
#                                                                 "LH72",   "RH70");

################################################################################

# my $c_keymap ='
# EQL, 1,   2,   3,   4,   5,   ESC,
# TAB, Q,   W,   E,   R,   T,   FN1,
# FN6, A,   S,   D,   F,   G,
# LSFT, Z,   X,   C,   V,   B,   LGUI,
# FN0, GRV, BSLS, LEFT, RGHT,
#                             FN7, FN8,
#                                  HOME,
#                       BSPC, DEL, END,
#     FN4,  6,  7,  8,   9,   0,   MINS,
#     FN2,  Y,  U,  I,   O,   P,   BSLS,
#     H,  J,  K,   L,   SCLN, QUOT,
#    LGUI, N,  M,  COMM, DOT, SLSH, RSFT,
#        UP, DOWN, LBRC, RBRC, RGUI,
# RALT, RCTL,
# PGUP,
# PGDN, ENT, SPC
# ';
#
# $c_keymap=~tr/\n/ /;
# $c_keymap=~s/\s+/ /g;
# keymap(split2wide(split(/,/,$c_keymap)));

################################################################################

$fh = FileHandle->new($ARGV[0],"r");

my $debug = 0;
my @comments = ();
my $in_kemap = 0;
my $keys = '';

if (defined $fh) {
  while(my $line=<$fh>){
    chomp($line);
    if ($in_keymap){
      if ($line=~m/(.*)\/\/(.*)/){
        $line = $1;
        $comment = $2;
        push(@comments,$comment) unless $comment=~m/(right|left) hand/;
      }
      if($line=~m/^\s*\),\s*$/){
        $in_keymap = 0;
        $keys=~tr/\n/ /;
        $keys=~s/\s+/ /g;
        keymap(split2wide(psplit(',',$keys)), join(" ",@comments));
        $keys=''; @comments = ();
        print ": OUT: $line\n" if $debug;
      }else{
        print ": IN: $line\n" if $debug;
        $keys=$keys." ".$line;
      }
    }else{
      if($line=~m/LAYOUT_ergodox\(/){
        $in_keymap = 1;
        if ($line=~m/(.*)\/\/(.*)/){
          $line = $1;
          $comment = $2;
          push(@comments,$comment) unless $comment=~m/(right|left) hand/;
        }
        print ": OUT: $line\n" if $debug;
      }else{
        print ": OUT: $line\n" if $debug;
      }
    }
  }
  undef $fh;
}
