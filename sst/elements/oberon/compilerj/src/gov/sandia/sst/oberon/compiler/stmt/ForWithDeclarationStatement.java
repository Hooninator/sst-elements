package gov.sandia.sst.oberon.compiler.stmt;

import gov.sandia.sst.oberon.compiler.exp.OberonExpression;
import gov.sandia.sst.oberon.compiler.exp.OberonExpressionException;
import gov.sandia.sst.oberon.compiler.exp.OberonIncompatibleTypeException;
import gov.sandia.sst.oberon.compiler.visitor.OberonStatementBodyVisitor;
import gov.sandia.sst.oberon.compiler.visitor.OberonVisitor;

public class ForWithDeclarationStatement extends ForStatement {

	protected DeclarationStatement declStmt;
	
	public ForWithDeclarationStatement(String fileName, int lineno, int colno,
			DeclarationStatement declStmt,
			OberonExpression loopCondition, AssignmentStatement incrStmt) {
		super(fileName, lineno, colno, loopCondition, incrStmt);
		
		this.declStmt = declStmt;
	}

	public DeclarationStatement getDeclarationStatement() {
		return declStmt;
	}
	
	public ForStatementType getForStatementType() {
		return ForStatementType.DECLARATION;
	}

	public int increaseAllocationByBytes() throws OberonIncompatibleTypeException {
		int incSize = 0;
		
		incSize += declStmt.increaseAllocationByBytes();
		
		for(OberonStatement stmt : statements) {
			incSize += stmt.increaseAllocationByBytes();
		}
		
		return incSize;
	}

	public int getDeclaredVariableSize() throws OberonIncompatibleTypeException {
		return increaseAllocationByBytes();
	}

	public void processVisitor(OberonVisitor visit) throws 
	OberonStatementException, OberonExpressionException {
		visit.visit(this);
	}

	public void visit(OberonStatementBodyVisitor visit) throws 
	OberonStatementException, OberonExpressionException {
		visit.visit(this);
	}

}
