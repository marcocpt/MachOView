//
//  NSString+Extensions.m
//  MachOView
//
//  Created by marcow on 2021/3/29.
//

#import "NSString+Extensions.h"

@implementation NSString (Extensions)

+ (NSString *)stringWithNibbles:(UInt32)nibbles {
  UInt32 X = (nibbles & 0xffff0000) >> 16;
  UInt32 Y = (nibbles & 0x0000ff00) >> 8;
  UInt32 Z = nibbles & 0x000000ff;
  if (Z == 0) {
    return [NSString stringWithFormat:@"%d.%d", X, Y];
  }
  return [NSString stringWithFormat:@"%d.%d.%d", X, Y, Z];
}

@end
