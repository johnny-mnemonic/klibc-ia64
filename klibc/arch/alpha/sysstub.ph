# -*- perl -*-
#
# arch/alpha/sysstub.ph
#
# Script to generate system call stubs
#

# On Alpha, most system calls follow the standard convention, with the
# system call number in r0 (v0), return an error value in r19 (a3) as
# well as the return value in r0 (v0).
#
# A few system calls are dual-return with the second return value in
# r20 (a4).

# In order to find errno, we need the gp, which is computed from the
# pv register.  This is two instructions, so the total length of the
# stub is 4x4 = 16 bytes.

sub make_sysstub($$$$@) {
    my($fname, $type, $sname, $stype, @args) = @_;

    $stype = $stype || 'common';
    $stype = 'common' if ( $stype eq 'dual0' );

    open(OUT, '>', "syscalls/${fname}.S");
    print OUT "#include <asm/unistd.h>\n";
    print OUT "#include <machine/asm.h>\n";
    print OUT "\n";
    print OUT "\t.text\n";
    print OUT "\t.type ${fname},\@function\n";
    print OUT "\t.ent\t${fname}, 0\n"; # What is this?
    print OUT "\t.globl ${fname}\n";
    print OUT "${fname}:\n";
    print OUT "\tldgp\tgp,0(pv)\n";
    print OUT "\tlda\tv0, __NR_${sname}(zero)\n";
    print OUT "\tbr __syscall_${stype}\n";
    print OUT "\t.size\t${fname},.-${fname}\n";
    print OUT "\t.end\t${fname}\n";
    close(OUT);
}

1;
