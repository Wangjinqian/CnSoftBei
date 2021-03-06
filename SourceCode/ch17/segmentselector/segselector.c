//-------------------------------------------------------------------
//	segselector.c 获取段寄存器中中各个段的段描述
//  //	本内核文件创建一个proc伪文件，'/proc/segselector'	
//  编译命令：$ make 
//  内核模块添加：$sudo insmod segselector.ko  
//  显示信息：$cat /proc/segselector
//  内核模块删除：$sudo rmmod segselector
//	programmer: <fs>
//	date begun: 20 OCT 2014
//-------------------------------------------------------------------

#include <linux/module.h>	// for init_module() 
#include <linux/proc_fs.h>	// for create_proc_read_entry() 
#include <linux/seq_file.h>
char modname[] = "segselector";

// using ‘global variables’ simplifies the inline assembly language 
short  _cs, _ds, _es, _fs, _gs, _ss;		// global variables

static int my_seqshow(struct seq_file *m, void *v)
{
	//asm( " mov %%cr3, %%eax \n mov %%eax, %0 " : "=m" (_cr3) :: "ax" );	
	asm(" mov  %cs, _cs  \n  mov %ds, _ds ");
	asm(" mov  %es, _es  \n  mov %fs, _fs ");
	asm(" mov  %gs, _gs  \n  mov %ss, _ss ");
	seq_printf(m, "CS=%04X  DS=%04X \n", _cs, _ds );
	seq_printf(m, "ES=%04X  FS=%04X \n", _es, _fs );
	seq_printf(m, "GS=%04X  SS=%04X \n", _gs, _ss );
	return 0; //!! must be 0, or will show nothing T.T
}

static int my_open(struct inode *inode, struct file *file)  
{  
    return single_open(file, my_seqshow, NULL);
}  

static const struct file_operations my_proc =   
{  
	.owner      = THIS_MODULE,  
	.open       = my_open,
	.read	    = seq_read,
	.llseek	    = seq_lseek,
	.release    = single_release,
}; 

static int __init showgdtmod_init( void )
{
	struct proc_dir_entry* my_proc_entry;
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	my_proc_entry = proc_create(modname, 0x644, NULL, &my_proc);
	return	0;  //SUCCESS
}


static void __exit showgdtmod_exit(void )
{
	remove_proc_entry( modname, NULL );

	printk( "<1>Removing \'%s\' module\n", modname );
}

module_init( showgdtmod_init );
module_exit( showgdtmod_exit );
MODULE_LICENSE("GPL"); 

