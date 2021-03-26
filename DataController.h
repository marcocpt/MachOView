/*
 *  DataController.h
 *  MachOView
 *
 *  Created by psaghelyi on 15/06/2010.
 *
 */

#define OFFSET_COLUMN       0
#define DATA_COLUMN         1   // use this with details
#define DESCRIPTION_COLUMN  2   // use this with details
#define VALUE_COLUMN        3

#define DATA_LO_COLUMN      1   // use this with no details
#define DATA_HI_COLUMN      2   // use this with no details

extern NSString * const MVUnderlineAttributeName;
extern NSString * const MVCellColorAttributeName;
extern NSString * const MVTextColorAttributeName;
extern NSString * const MVMetaDataAttributeName;

extern NSString * const MVLayoutUserInfoKey;
extern NSString * const MVNodeUserInfoKey;
extern NSString * const MVStatusUserInfoKey;
extern NSString * const MVStatusPenddingKey;

extern NSString * const MVDataTreeWillChangeNotification;   ///< 未使用
extern NSString * const MVDataTreeDidChangeNotification;    ///< 未使用
extern NSString * const MVDataTreeChangedNotification;      ///< Document.handleDataTreeChanged:
extern NSString * const MVDataTableChangedNotification;
extern NSString * const MVThreadStateChangedNotification;

extern NSString * const MVStatusTaskStarted;
extern NSString * const MVStatusTaskPendding;
extern NSString * const MVStatusTaskTerminated;

struct MVNodeSaver;

@protocol MVSerializing <NSObject>
- (void)loadFromFile:(FILE *)pFile;
- (void)saveToFile:(FILE *)pFile;
- (void)clear;
@end

//----------------------------------------------------------------------------
@interface MVColoumns : NSObject
{
  NSString *            offsetStr;      ///< pFile, Address, Offset
  NSString *            dataStr;        ///< Data, Data LO
  NSString *            descriptionStr; ///< Description, Data HI
  NSString *            valueStr;       ///< Value
}

@property (nonatomic)   NSString * offsetStr;         ///< pFile, Address, Offset
@property (nonatomic)   NSString * dataStr;           ///< Data, Data LO
@property (nonatomic)   NSString * descriptionStr;    ///< Description, Data HI
@property (nonatomic)   NSString * valueStr;          ///< Value

/// 使用参数设置 MVColoumns 属性
/// @param col0 offsetStr
/// @param col1 dataStr
/// @param col2 descriptionStr
/// @param col3 valueStr
+(MVColoumns *) coloumnsWithData:(NSString *)col0 :(NSString *)col1 :(NSString *)col2 :(NSString *)col3;

@end

//----------------------------------------------------------------------------
@interface MVRow : NSObject <MVSerializing>
{
  MVColoumns *          coloumns;         ///< 存储表格视图中显示的一行中各列的字符串数据
  NSDictionary *        attributes;
  uint32_t              offset;           ///< for sorting if necessary
  uint32_t              coloumnsOffset;   ///< offset of coloumns
  uint32_t              attributesOffset; ///< offset of attribues
  BOOL                  deleted;
  BOOL                  dirty;            ///< eg. attributes has changed
}

@property (nonatomic)   NSDictionary * attributes;
@property (nonatomic)   MVColoumns * coloumns;      ///< 存储表格视图中显示的一行中各列的字符串数据
@property (nonatomic)   uint32_t offset;
@property (nonatomic)   BOOL deleted;
@property (nonatomic)   BOOL dirty;

-(NSString *)coloumnAtIndex:(NSUInteger)index;

@end

@class MVArchiver;

//----------------------------------------------------------------------------
@interface MVTable : NSObject
{
  NSMutableArray<MVRow *>*      rows;         ///< array of MVRow * (host of all the rows)
  NSMutableArray<MVRow *>*      displayRows;  ///< array of MVRow * (rows filtered by search criteria)
  MVArchiver *          __weak archiver;
  FILE *                swapFile;
  NSLock *              tableLock;
}

@property (nonatomic)   FILE * swapFile;

- (NSUInteger)          rowCountToDisplay;
- (MVRow *)             getRowToDisplay:(NSUInteger)rowIndex;

- (void)                popRow;
- (void)                appendRow:(id)col0 :(id)col1 :(id)col2 :(id)col3;
- (void)                insertRowWithOffset:(uint32_t)offset :(id)col0 :(id)col1 :(id)col2 :(id)col3;
- (void)                updateCellContentTo:(id)object atRow:(NSUInteger)rowIndex andCol:(NSUInteger)colIndex;

- (NSUInteger)          rowCount;
- (void)                setAttributes:(NSString *)firstArg, ... NS_REQUIRES_NIL_TERMINATION;
- (void)                setAttributesForRowIndex:(NSUInteger)index :(NSString *)firstArg, ... NS_REQUIRES_NIL_TERMINATION;
- (void)                setAttributesFromRowIndex:(NSUInteger)index :(NSString *)firstArg, ... NS_REQUIRES_NIL_TERMINATION;

@end

//----------------------------------------------------------------------------
@interface MVNode : NSObject <MVSerializing>
{
  NSString *            caption;          ///< 节点标题
  MVNode *              __weak parent;    ///< 父节点
  NSMutableArray *      children;         ///< 子节点
  NSRange               dataRange;        ///< 节点对应源文件中的数据范围
  MVTable *             details;
  NSMutableDictionary * userInfo;
  uint32_t              detailsOffset;
}

@property (nonatomic)                   NSString *            caption;        ///< 节点标题, 作为侧边栏列表的标题
@property (nonatomic,weak)              MVNode *              parent;         ///< 父节点
@property (nonatomic)                   NSRange               dataRange;      ///< 节点的数据范围
@property (nonatomic)                   MVTable *             details;
/// 包含 MVLayoutUserInfoKey, MVNodeUserInfoKey, MVStatusUserInfoKey, MVStatusPenddingKey
@property (nonatomic)                   NSMutableDictionary * userInfo;
@property (nonatomic)                   uint32_t              detailsOffset;

- (NSUInteger)          numberOfChildren;
- (MVNode *)            childAtIndex:(NSUInteger)n;

/// 插入子节点
/// @param _caption 节点标题
/// @param location 起始位置
/// @param length 长度
- (MVNode *)            insertChild:(NSString *)_caption location:(uint32_t)location length:(uint32_t)length;


/// 插入子节点, 初始化节点的 details, 并把生成的子节点赋给 saver.m_node
/// @param _caption 节点标题
/// @param location 起始位置
/// @param length 长度
/// @param saver <#saver description#>
- (MVNode *)            insertChildWithDetails:(NSString *)_caption location:(uint32_t)location length:(uint32_t)length saver:(MVNodeSaver &)saver;
- (MVNode *)            findNodeByUserInfo:(NSDictionary *)uinfo;
- (void)                openDetails;  // open swap file for reading details on demand
- (void)                closeDetails; // close swap file
- (void)                sortDetails;
- (void)                filterDetails:(NSString *)filter;
- (void)                loadFromFile:(FILE *)pFile;
- (void)                saveToFile:(FILE *)pFile;

@end

//----------------------------------------------------------------------------
@interface MVDataController : NSObject
{
  NSString *            fileName;         ///< path to the binary handled by this data controller
  NSMutableData *       fileData;         ///< content of the binary
  NSMutableData *       realData;         ///< patched content by relocs and bindings
  NSMutableArray *      layouts;          ///< 包含 MVLayout 的子类: FatLayout, MachOLayout, ArchiveLayout
  MVNode *              rootNode;
  MVNode *              __weak selectedNode;
  NSLock *              treeLock;         ///< semaphore for the node tree
}

@property (nonatomic)                   NSString *      fileName;       ///< path to the binary handled by this data controller
@property (nonatomic)                   NSMutableData * fileData;       ///< content of the binary
@property (nonatomic)                   NSMutableData * realData;       ///< patched content by relocs and bindings

/**
 包含 MVLayout 的子类: FatLayout, MachOLayout, ArchiveLayout
 @discussion
 1. 胖文件: 包含 FatLayout 和 各种架构的 MachOLayout

 2. 普通文件: 包含一个 MachOLayout
 
 3. 魔数未定义: ArchiveLayout 文件
*/
@property (nonatomic,readonly)          NSArray *       layouts;
@property (nonatomic,readonly)          MVNode *        rootNode;
@property (nonatomic,weak)              MVNode *        selectedNode;
@property (nonatomic,readonly)          NSLock *        treeLock;

/// 获取 cpu 类型的字符串
-(NSString *)           getMachine:(cpu_type_t)cputype;
/// 获取 ARM  cpu 类型的字符串, 根据子 cpu 类型判断.
-(NSString *)           getARMCpu:(cpu_subtype_t)cpusubtype;

/**
 根据 magic 创建对应的布局.
 @discussion
 未知魔数创建 ArchiveLayout
 */
- (void)                createLayouts:(MVNode *)parent location:(uint32_t)location length:(uint32_t)length;

/// 投递通知 MVDataTreeChangedNotification
- (void)                updateTreeView: (MVNode *)node;

/// 投递通知 MVDataTableChangedNotification
- (void)                updateTableView;
- (void)                updateStatus: (NSString *)status;
- (void)updateStatus: (NSString *)status :statusString;

@end

//----------------------------------------------------------------------------
@interface MVArchiver : NSObject
{
  NSString *            swapPath;       ///< 交换文件的路径
  NSMutableArray *      objectsToSave;  ///< conforms MVSerializing, 待保存的对象
  NSThread *            saverThread;
  NSLock *              saverLock;
}

@property (nonatomic,readonly)  NSString * swapPath;  ///< 交换文件的路径

/// 初始化各属性, 并在 path 的文件写入头部信息: "!<MachoViewSwapFile 1.0>\n"
/// @param path 设定 swapPath
+(MVArchiver *) archiverWithPath:(NSString *)path;
-(void) addObjectToSave:(id)object;
-(void) suspend;
-(void) resume;
-(void) halt;

@end

//----------------------------------------------------------------------------
struct MVNodeSaver
{
  MVNodeSaver();
  ~MVNodeSaver();
  
  /// 设置m_node 参数
  void setNode(MVNode * node) { m_node = node; }
  
private:
  MVNodeSaver(MVNodeSaver const &);
  MVNodeSaver & operator=(MVNodeSaver const &);
  
  MVNode * __weak m_node;
};


