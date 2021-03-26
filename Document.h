/*
 *  Document.h
 *  MachOView
 *
 *  Created by psaghelyi on 15/06/2010.
 *
 */

@class MVDataController;

@interface MVOutlineView : NSOutlineView
{
}
@end

@interface MVTableView : NSTableView
{
}
@end

@interface MVRightFormatter : NSFormatter
{
  BOOL        compound;   // NO: plain hex;     YES: groups of bytes (11 22 33 44 55)
  NSUInteger  length;     // size of hex value; number of bytes 
  BOOL        alignLeft;  // NO: 12 --> 0012    YES: 12 --> 1200
}
@end


@interface MVDocument : NSDocument
{
  IBOutlet MVOutlineView *        leftView;           ///< 左边列表视图
  IBOutlet MVTableView *          rightView;          ///< 主窗口表格视图
  IBOutlet NSSearchField *        searchField;        ///< 搜索框字段
  IBOutlet NSTextField *          statusText;         ///< 底部状态栏字段
  IBOutlet NSProgressIndicator *  progressIndicator;
  IBOutlet NSSegmentedControl *   offsetModeSwitch;
  IBOutlet NSButton *             stopButton;
  MVDataController *              dataController;
  int32_t                         threadCount;
}
@property (nonatomic,readonly) MVDataController * dataController;

- (IBAction)updateSearchFilter:(id)sender;
- (IBAction)updateAddressingMode:(id)sender;
- (IBAction)stopProcessing:(id)sender;
- (BOOL)isRVA;

+ (NSString *)temporaryDirectory;

@end
