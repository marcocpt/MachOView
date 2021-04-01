//
//  NSString+Extensions.h
//  MachOView
//
//  Created by marcow on 2021/3/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (Extensions)

/// X.Y.Z is encoded in nibbles xxxx.yy.zz
+ (NSString *)stringWithNibbles:(UInt32)nibbles;

@end

NS_ASSUME_NONNULL_END
